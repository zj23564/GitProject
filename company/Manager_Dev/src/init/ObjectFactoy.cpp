/***************************************************************
 * Name:      ObjectFactoy.cpp
 * Purpose:   Code for Application Class
 * Author:    xrg (xrg_1@yhaoo.com)
 * Created:   2011-10-16
 * Copyright: xrg (xrgsunnning.com)
 * License:
 **************************************************************/

#include "../../include/init/ObjectFactoy.h"
#include <stdlib.h>
#include "stdio.h"
#include<libxml/parser.h>
#include<libxml/tree.h>
#include "../../include/userJob/UserloginJob.h"
#include "../../include/send/SendObject.h"
#include "../../include/define/Define.h"
#include "../../include/log/write_log.h"
#include "../../Device_Data.h"
#include "../../Device_Job.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../../GlobalFunc.h"

extern int log_count;
ObjectFactoy * ObjectFactoy::p_Factory=NULL;
CMutex ObjectFactoy::m_sMutex;
CMutex ObjectFactoy::m_queueMutex;
CMutex ObjectFactoy::m_queueSendMutex;
sem_t ObjectFactoy::sem;
sem_t ObjectFactoy::start;
sem_t ObjectFactoy::sem_deal;

sem_t ObjectFactoy::sem_send;
sem_t ObjectFactoy::start_chk_send;
sem_t ObjectFactoy::sem_deal_send;

sem_t ObjectFactoy::start_device;
sem_t ObjectFactoy::sem_device;
sem_t ObjectFactoy::sem_deal_device;
sem_t ObjectFactoy::sem_scanf;

bool ObjectFactoy::flag = 0;
bool ObjectFactoy::flag_send = 0;
bool ObjectFactoy::flag_device = 0;
queue<QueueData*> ObjectFactoy::m_queue;
queue<QueueSendData*> ObjectFactoy::m_sendaddr;
queue<DEVICE_DATA* > ObjectFactoy::m_device_data;
QueueData*    ObjectFactoy::m_qData=NULL;
DEVICE_DATA* ObjectFactoy::device_data = NULL;
ObjectFactoy::ObjectFactoy():PacketType(-1),m_ThreadMag(4)
 {
      queue_size = 0;
      device_data = NULL;
      login_user_sid = 0;
      fd_log = NULL;
      fd_storage = NULL;
      fd_stream = NULL;
      fd_alarm = NULL;

     memcpy(m_AlarmServer.m_Addr,"192.168.1.81",32);
     m_AlarmServer.m_Port = 8800;
     memcpy(m_StreamServer.m_Addr,"192.168.1.80",32);
     m_StreamServer.m_Port = 8000;
     memcpy(m_LogServer.m_Addr,"192.168.1.86",32);
     m_LogServer.m_Port = 4500;
     memcpy(m_TVWallServer.m_Addr,"192.168.1.121",32);
     m_TVWallServer.m_Port = 8001;
     memcpy(m_StorageServer.m_Addr,"192.168.1.181",32);
     m_StorageServer.m_Port = 8888;

    fd_log = Tcp_Connect(m_LogServer.m_Addr,m_LogServer.m_Port,NULL,Event_Sys,NULL,1,0);
    if(fd_log == NULL)
        printf("connect fail\n");
 }
 ObjectFactoy::~ObjectFactoy()
 {


 }
ObjectFactoy * ObjectFactoy::GetFactoryInstance()
 {
     if(NULL == p_Factory)
     {
         p_Factory=new  ObjectFactoy();

     }
     return p_Factory;
 }
 int nn = 1;
 void ObjectFactoy::GetData(conn_t *conn, char *buf, int len, void *context)
 {
	printf("get data   buff len  is  %d  >>>>>>>>>>   nn = %d\n",len,nn);
	nn++;
         if(((LPHEAD)buf)->SysMark !=NET_SYSTEM_MASK_HTP){
              printf("error data \n");
              return;
         }
         m_qData = new QueueData;
         m_queueMutex.lock();
         m_qData->Buf=new char[len];
         memcpy(m_qData->Buf,buf,sizeof(char)*len);
         m_qData->fd = conn;
         m_qData->Buflen = len;
         m_queue.push(m_qData);
         m_queueMutex.unlock();
         if(flag)
          sem_post(&(ObjectFactoy::start));

}

int ObjectFactoy::GetQueueSize()
{
    int Size=-1;
    m_queueMutex.lock();
    Size=m_queue.size();
    m_queueMutex.unlock();
    if(-1 == Size)
    {
        printf("Get Queue Size ERR!!!!!!!!!!");
    }
    return Size;
}

void ObjectFactoy::DealqueueData()
{

    m_queueMutex.lock();
        while(m_queue.size()!=0)
        {
          CJob * job=GetJobObject(m_queue.front());
          m_ThreadMag.Run(job,(void *)m_queue.front());
          m_queue.pop();
        }
    m_queueMutex.unlock();
    flag = 1;
    sem_post(&ObjectFactoy::sem);
    sem_wait(&(ObjectFactoy::sem_deal));

}



CJob * ObjectFactoy::GetJobObject(QueueData * Data)
{
    CJob * Job = NULL;
    PacketType=((LPHEAD)Data->Buf)->PackType;
    unsigned long nModuleType = ((LPHEAD)Data->Buf)->ModuleMark;
    int sessionID = ((LPHEAD)Data->Buf)->SessionID;
    Job = (CJob *)(new UserloginJob(sessionID,Data->fd));
    return Job;
}


void ObjectFactoy::GetJob_Send()
{
    CJob * Job = NULL;
    while(m_sendaddr.size()!=0)
    {
        m_queueSendMutex.lock();
        QueueSendData* SendData = m_sendaddr.front();
        Job = (CJob*)new SendObject(SendData->fd,((HEAD*)(SendData->Send))->PackSize);
        m_ThreadSend.Run(Job,(void *)m_sendaddr.front());
        m_sendaddr.pop();
        m_queueSendMutex.unlock();
    }

    flag_send = 1;
    sem_post(&ObjectFactoy::sem_send);
    sem_wait(&ObjectFactoy::sem_deal_send);
}
/**********************************接受设备数据******************************/
void ObjectFactoy::GetData_Device(conn_t *fd, char *buf, int len, void *context)
{
    printf("getdata  len is >>>>>>>> \n%d\n",len);
    device_data = new DEVICE_DATA;
    device_data->buff = new char[len];
    memcpy(device_data->buff,buf,len);
    device_data->fd = fd;
    device_data->len = len;
    m_device_data.push(device_data);
    device_data = NULL;

     if(flag_device)
      sem_post(&(ObjectFactoy::start_device));
}

void ObjectFactoy::DealqueueDeviceData()
{
   //     printf("run DealqueueDeviceData()\n");
        CJob * Job = NULL;
        while(0 != m_device_data.size()){
                DEVICE_DATA*  data = m_device_data.front();
//                printf("data->buff is\n%s\n****************\n",data->buff);
//                printf("data->fd is\n%d\n****************\n",data->fd);
//                printf("data->len is\n%d\n****************\n",data->len);


                int flag = Ans_Xml(data);
//             //   printf("flag is >>>>>>>>>>>   %d\n",flag);
                Job = new Device_Job(flag,data);
                m_ThreadSend.Run(Job,(void *)data);
                Job = NULL;
                m_device_data.pop();

        }

    flag_device = 1;
    sem_post(&ObjectFactoy::sem_device);
    sem_wait(&(ObjectFactoy::sem_deal_device));


}

int ObjectFactoy::Ans_Xml(DEVICE_DATA* data)
{

        int flag = 0;
        xmlDocPtr doc;
        xmlNodePtr root,node,res;
        xmlChar *rt,*id,*passwd,*type,*ns;
   //     int fd = 0;;
        printf("in ans_xml buff i s\n*********************\n %s\n*******************\n ",data->buff);
  //      xmlNodePtr root,node;
        //xmlChar *rt,*result,*addr,*port,*ns;
        doc = xmlParseMemory(data->buff,data->len);
        if(doc == NULL){
           //     printf("file is NULL\n");
                return 0;
        }
        root = xmlDocGetRootElement(doc);
        for(node = root->children;node;node = node->next){
                //printf("node name is\n%s\n",node->name);
                if(xmlStrcasecmp(node->name,BAD_CAST"query")==0){
                        char* p = strtok((char*)(node->ns->href),":");
                        p=strtok(NULL,":");
                        p=strtok(NULL,":");

                        if(0==strcmp(p,"querylb")){
                      //  	printf("device serch\n");
                        	flag = 1;

/*************解析出设备的ID 和密码 还有类型*****************/

							break;
                        }
                        else if(0==strcmp(p,"register")){
                       	printf("device register\n");
                        	flag = 2;
                        //	char* add_tmp = new char[sizeof(DEVICE)];
                        //	DEVICE* add = (DEVICE*)add_tmp;
                        	DEVICE* add = new DEVICE;
                        int ID = 0;
                      for(res = node->children;res;res = res->next){
                     //   printf("res name is  %s\n",res->name);
                        if(xmlStrcasecmp(res->name,BAD_CAST"id")==0){
                                id = xmlNodeGetContent(res);

                                memcpy(add->name,(char*)id,strlen((char*)id));
                                ID = atoi(add->name);
                                add->ID = ID;
                               printf("id  is\n  %d\n",ID );
                            }
                        else if(xmlStrcasecmp(res->name,BAD_CAST"passwd")==0){
                                passwd = xmlNodeGetContent(res);
                                printf("passwd is\n  %s\n",passwd);
                            }

                        else if(xmlStrcasecmp(res->name,BAD_CAST"type")==0){
                                type = xmlNodeGetContent(res);
                                printf("type is\n  %s\n",type);
                                add->type = atoi((char*)type);
                            }
                        }

                        if(NULL != m_MemData.Device_map[ID]){

                            //将设备状态写入到设备节点表中（所有的设备节点都在这个表中）
                            m_MemData.Device_map[ID]->device.status = DEVICE_STATUS_ONLINE;
                            char IP[32];
                            char* IP_out;
                            Tcp_GetRemoteAddr(data->fd,IP,32);
                            IP_out = strtok(IP,":");
                            //memcpy((m_MemData.Device_map[ID])->device.IP,IP_out,strlen(IP_out));
                          //  printf("new device IP is  %s\n",(m_MemData.Device_map[ID])->device.IP);

                            //将上线的设备加入到在线设备表的表中
                            LOG_DEVICE* log_dev = new LOG_DEVICE;
                            log_dev->device = add;
                            log_dev->fd = data->fd;
                            Login_device[(int)data->fd] = log_dev;
                        }
                        else{

                            delete add;//新链接的设备不符合要求，删除
                        }

                  //      printf("Login_device.size is   %d\n",Login_device.size());
                        xmlFree(id);
                        xmlFree(passwd);
                        xmlFree(type);
                    /**********************************************/
							break;
                        }
                        else if(0==strcmp(p,"heartbeat")){
                            flag = 3;
							break;
                        }
                        else if(0==strcmp(p,"alarm")){
							printf("device alarm\n");
							flag = 4;
							break;
                        }
                        p = NULL;

                }
        }
        xmlFreeDoc(doc);
        return flag;
}

void ObjectFactoy::Gettime(void)
{
        time_t tim;
        struct tm * nowtime;
        time(&tim);
        nowtime = localtime(&tim);

        int year = nowtime->tm_year+1900;
        int mon = nowtime->tm_mon+1;
        int day = nowtime->tm_mday;
        int hour = nowtime->tm_hour;
        int min = nowtime->tm_min;
        int sec = nowtime->tm_sec;


        char tmpbuf[512] = {0};
        sprintf(tmpbuf,"%d%02d%02d%02d%02d%02d",year,mon,day,hour,min,sec);
        sprintf(timebuff,"<iq type='set'>\n  <query xmlns='posacar:signaling:heartbeat'>\n    <time>%s</time>\n  </query>\n</iq>",tmpbuf);


}

void ObjectFactoy::ReadXml()
{
      int sfd;
      sfd=open("xml.xml",O_RDWR);
      if(sfd<0){
        perror("open sound");
        exit(EXIT_FAILURE);
      }
      read(sfd,read_buff1,1024);
      close(sfd);

      sfd=open("request.xml",O_RDWR);
      if(sfd<0){
        perror("open sound");
        exit(EXIT_FAILURE);
      }
      read(sfd,read_buff2,1024);
      close(sfd);

      sfd=open("request2.xml",O_RDWR);
      if(sfd<0){
        perror("open sound");
        exit(EXIT_FAILURE);
      }
      read(sfd,read_buff3,1024);
      close(sfd);

}

void ObjectFactoy::Change_Device_Status(int ID)
{
    if(m_MemData.Device_map[ID] != NULL){
        m_MemData.Device_map[ID]->device.status = DEVICE_STATUS_OFFLINE;
    }
    else{
        printf("there is no such device\n");
    }

}

//处理掉线，给主控台和报警服务器发送掉线报警信号
void ObjectFactoy::Deal_Device_LineOff(void)
{

}
