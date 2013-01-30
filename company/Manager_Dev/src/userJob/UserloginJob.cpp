
#include "../../include/userJob/UserloginJob.h"
#include "../../HT_Platform_ResultCode.h"
#include "../../include/define/Define_Page.h"
#include "../../include/log/log_data.h"
#include "../../include/log/write_log.h"
#include "../../include/log/write_log.h"
#include <iostream>
#include <time.h>
#include <sstream>
using namespace std;
extern unsigned long Seccesion;
extern map<unsigned long,string>log_map;
extern MYSQL mysql;
extern ObjectFactoy *m_fator;

int UserloginJob::session_ID = 0;
UserloginJob::UserloginJob()
{

    //m_UserIP = NULL;
    AllDeviceBuff = NULL;
    m_fd = 0;
}

UserloginJob::UserloginJob(int sessionID,conn_t* fd)
{
    m_fd=fd;
    m_sessionID = sessionID;
}

UserloginJob::~UserloginJob()
{
    printf("delete qdata\n");
    delete [] qdata->Buf;
    delete qdata;
//    delete send_info->node_count;
//    delete send_info;
}
int   UserloginJob::GetTime()
{
    time_t tim;
    struct tm * nowtime;
    time(&tim);
    nowtime = localtime(&tim);
    printf("tim is %d\n",tim);
    return (int )tim;
}



void UserloginJob::Run(void *jobData)
{
        qdata = (QueueData *)jobData;
        Sysmark = ((LPHEAD)qdata->Buf)->SysMark;
        nModuleType = ((LPHEAD)qdata->Buf)->ModuleMark;
        packType = ((LPHEAD)qdata->Buf)->PackType;
        if(Sysmark == NET_SYSTEM_MASK_HTP)
               switch(nModuleType)
               {
                   case NET_MOUDLE_MASK_ALM :   //报警
                   {
                       MCS(packType);
                        break;
                   }
                   case NET_MOUDLE_MASK_MSS:        //流媒体
                   {
                       printf("流媒体\n");
                       MCS(packType);
                        break;
                   }
                   case NET_MOUDLE_MASK_LOG:        //日志
                   {
                        printf("log centor\n");
                        MCS(packType);
                       break;
                   }
                   case NET_MOUDLE_MASK_MCS:        //管理中心
                   {
                       printf("管理中心\n");
                         MCS(packType);

                        printf("管理中心操作完成\n");
                    break;
                   }

                   case NET_MOUDLE_MASK_STG:        //存储
                   {
                        printf("存储模块\n");
                        MCS(packType);
                       printf("存储模块操作完成\n");
                       break;
                   }
                   case NET_MOUDLE_MASK_SMT:        //智能
                   {
                       printf("智能分析模块\n");
                        MCS(packType);
                       printf("智能分析模块操作完成\n");
                       break;
                   }
                   case NET_MOUDLE_MASK_USER:       //用户登录
                   {
                       printf("用户操作\n");
                         MCS_USER(packType);
                        printf("用户操作完成\n");
                        break;
                   }
                   default:
                        break;
        }


}


void UserloginJob::AllUser_Block()
{
}

void UserloginJob::AllUser()
{
    printf("send user tree data2\n");
  //  char* block = m_fator->m_MemData.Get_UserBlock_Ptr();

    map<string,USERINFO*>::iterator ite;
    int size = m_fator->m_MemData.User_map.size();
    char * buff = new char[sizeof(USERINFO)*size+sizeof(USERCOUNT)];
    memset(buff,0,sizeof(USERINFO)*size+sizeof(USERCOUNT));
    memcpy(buff,m_fator->m_MemData.Get_AllUser_Count(),sizeof(USERCOUNT));

    int i = 0;
    for(ite = m_fator->m_MemData.User_map.begin();ite!=m_fator->m_MemData.User_map.end();ite++){
        memcpy(buff+sizeof(USERCOUNT)+i*sizeof(USERINFO),ite->second,sizeof(USERINFO));
        i++;
    }
    Request_Data(NET_PACKTYPE_MCS_RESPONSEUSERS,buff,HT_PLATFORM_RESULTCODE_SUCESS,0,sizeof(USERINFO)*size+sizeof(USERCOUNT));

}


void UserloginJob::Modify_passwd()
{
        USERINFO* tmp = m_fator->login_user[m_sessionID];   //If the user is logged in
        MODIFY_PASSWD* pwd = (MODIFY_PASSWD*)((qdata->Buf)+sizeof(HEAD));
        if(tmp == NULL){
            Request_Data(NET_PACKTYPE_MCS_MODIFYPASSWORD,NULL,HT_PLATFORM_RESULTCODE_NOUSER,m_sessionID,0);
            return;
        }
        else if(strcmp(tmp->PassWord,pwd->Oldpasswd) != 0){
            Request_Data(NET_PACKTYPE_MCS_MODIFYPASSWORD,NULL,HT_PLATFORM_RESULTCODE_ERRORPSWD,m_sessionID,0);
            return;
        }

        memset(tmp->PassWord,0,16);
        memcpy(tmp->PassWord,pwd->passwd,16);
        printf("MODIFY_PASSWD usr name  %s  \n",tmp->Name);
        printf("MODIFY_PASSWD usr pwd  %s  \n",pwd->passwd);
        stringstream sql;
        sql <<"update user_new set user_pwd='"<<tmp->PassWord<<"' where ID="<<tmp->ID<<";";
        string terminal = sql.str();
        mysql_query(&mysql,terminal.data());
        Request_Data(NET_PACKTYPE_MCS_MODIFYPASSWORD,NULL,HT_PLATFORM_RESULTCODE_SUCESS,m_sessionID,0);
}

void UserloginJob::Query_Power()
{
    USERINFO* tmp = m_fator->login_user[m_sessionID];   //If the user is logged in
    printf("****************************************\n");
     printf("login usr name %s  \n",tmp->Name);
    printf("****************************************\n");
    printf("query session id is %d  \n",m_sessionID);
    if(tmp == NULL){
        printf("no such user loged in\n");
        Request_Data(NET_PACKTYPE_MCS_RESPONSE_QUERYPOWER,NULL,HT_PLATFORM_RESULTCODE_NOUSER,0,0);
        return;
    }
        Request_Data(NET_PACKTYPE_MCS_RESPONSE_QUERYPOWER,(char*)tmp,HT_PLATFORM_RESULTCODE_SUCESS,m_sessionID,sizeof(USERINFO));
}



void UserloginJob::Request_Device()
{

    int result = 0;

    result = HT_PLATFORM_RESULTCODE_SUCESS; //暂时默认
    HEAD head;
    head.SysMark = NET_SYSTEM_MASK_HTP;
    head.ModuleMark = NET_MOUDLE_MASK_MCS;
    head.PackType = NET_PACKTYPE_MCS_RESPONSE_DEVICETREE;
    head.ResultCode = result;

    COUNT* node_count = m_fator->m_MemData.Get_AllDev_Count();

    head.PackSize = sizeof(COUNT)+sizeof(HEAD)+sizeof(MSSINFO)+(node_count->Count_Group)*sizeof(DEVICE_GRP)+(node_count->Count_Device)*sizeof(DEVICE)+(node_count->Count_Channel)*sizeof(DEVICE_CHANNEL);
    head.DataSize = head.PackSize-sizeof(HEAD)-sizeof(MSSINFO);

    char* buff = NULL;
    printf("package size is %d\n",head.PackSize);
    buff = new char[head.PackSize];
                       /*************暂时写死流媒体Ip和端口******************/
    memcpy(m_fator->mssinfo.IP ,"192.168.1.84",14);
    m_fator->mssinfo.port = 3000;
                       /************************************************/
    memcpy(buff,&head,sizeof(HEAD));
    memcpy(buff+sizeof(HEAD),&(m_fator->mssinfo),sizeof(MSSINFO));
    memcpy(buff+sizeof(HEAD)+sizeof(MSSINFO),node_count,sizeof(COUNT));
    printf("count dev_group is %d\n",node_count->Count_Group);
    printf("count dev is %d\n",node_count->Count_Device);
    printf("count channel is %d\n",node_count->Count_Channel);
    printf("size of HEAD is %d  size of MSSINFO is %d\n",sizeof(HEAD),sizeof(MSSINFO));
    int i = 0;

    map<int,NODE_GRP*>::iterator it_dev_grp;

    for(it_dev_grp = m_fator->m_MemData.DeviceGrp_map.begin();it_dev_grp!=m_fator->m_MemData.DeviceGrp_map.end();it_dev_grp++){
        NODE_GRP* grp = it_dev_grp->second;
        memcpy(buff+sizeof(HEAD)+sizeof(MSSINFO)+sizeof(COUNT)+i*sizeof(DEVICE_GRP),&(grp->device_grp),sizeof(DEVICE_GRP));
        i++;
    }
    i = 0;
    map<int,NODE*>::iterator it_dev;
    for(it_dev = m_fator->m_MemData.Device_map.begin();it_dev!=m_fator->m_MemData.Device_map.end();it_dev++){
        NODE* dev = it_dev->second;
        memcpy(buff+sizeof(HEAD)+sizeof(MSSINFO)+sizeof(COUNT)+node_count->Count_Group*sizeof(DEVICE_GRP)+i*sizeof(DEVICE),&(dev->device),sizeof(DEVICE));
    i++;
    }


    i = 0;
    map<int,DEVICE_CHANNEL*>::iterator it_chn;
    for(it_chn = m_fator->m_MemData.DeviceChnnel_map.begin();it_chn!=m_fator->m_MemData.DeviceChnnel_map.end();it_chn++){
        DEVICE_CHANNEL* chn = it_chn->second;
//        printf("channel.name is >>>> %s \n",chn->name);
//        printf("channel.ID is >>>> %d \n",chn->ID);
//        printf("channel.PID is >>>> %d \n",chn->group_ID);
        memcpy(buff+sizeof(HEAD)+sizeof(MSSINFO)+sizeof(COUNT)+node_count->Count_Group*sizeof(DEVICE_GRP)+node_count->Count_Device*sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),chn,sizeof(DEVICE_CHANNEL));
       DEVICE_CHANNEL* t_chn  =(DEVICE_CHANNEL*) (buff+sizeof(HEAD)+sizeof(MSSINFO)+sizeof(COUNT)+node_count->Count_Group*sizeof(DEVICE_GRP)+node_count->Count_Device*sizeof(DEVICE));
        printf("channel.name is >>>> %s \n",(t_chn+i)->name);
        printf("channel.ID is >>>> %d \n",(t_chn+i)->ID);
        printf("channel.PID is >>>> %d \n",(t_chn+i)->group_ID);
      i++;
    }
    printf("send dev tree data\n");
    Push_SendData(buff,m_fd);

}
void UserloginJob::Requset_PowerTree()      //request powerTree
{
      printf("send power tree data\n");
    COUNT* node_count = m_fator->m_MemData.Get_AllDev_Count();
    map<int,LIMIT*>::iterator   ite;
    char* buff = new char[((m_fator->m_MemData.Power_map).size())*sizeof(LIMIT)+sizeof(COUNT)];
    memcpy(buff,node_count,sizeof(COUNT));
    int i =0;
    for(ite = (m_fator->m_MemData.Power_map).begin();ite!=(m_fator->m_MemData.Power_map).end();ite++){
        memcpy(buff+sizeof(COUNT)+i*sizeof(LIMIT),ite->second,sizeof(LIMIT));
        i++;
    }
    Request_Data(NET_PACKTYPE_MCS_REQUEST_POWER_TREE,buff,HT_PLATFORM_RESULTCODE_SUCESS,0,((m_fator->m_MemData.Power_map).size())*sizeof(LIMIT)+sizeof(COUNT));
}

void UserloginJob::Request_StreamTree()
{
    COUNT* node_count = m_fator->m_MemData.Get_AllDev_Count();
    char* buff = new char[sizeof(MONITOR_CENTER)*node_count->Count_Stream+sizeof(COUNT)];
    memcpy(buff,node_count,sizeof(COUNT));
    map<int,MONITOR_CENTER*>::iterator   ite;
    int i = 0;
    for(ite = m_fator->m_MemData.monitor_map.begin();ite != m_fator->m_MemData.monitor_map.end();ite++){
        memcpy(buff+sizeof(COUNT)+i*sizeof(MONITOR_CENTER),ite->second,sizeof(MONITOR_CENTER));
        printf("centor name is %s\n",((MONITOR_CENTER*)(ite->second))->name);
        i++;
    }
    Request_Data(NET_PACKTYPE_MCS_REQUEST_STREAM_TREE,buff,HT_PLATFORM_RESULTCODE_SUCESS,0,sizeof(MONITOR_CENTER)*node_count->Count_Stream+sizeof(COUNT));
    delete [] buff;
}


void UserloginJob::Request_DeviceStatus()
{
        printf("reuqest_device status\n");


}



void UserloginJob::Del_DeviceGrp()
{
 /*解析规则：
        包数据包含  HEAD+MCSUSERLOGIN+COUNT+设备分组ID+设备节点ID；
        COUNT。Count_Group == 被删除分组的节点中包含的下属分组节点数目
        COUNT.Count_Device == 被删除的分组中下属所有节点所包含的设备节点数目;
  */
    COUNT m_count;
    memcpy(&m_count,(qdata->Buf)+sizeof(HEAD),sizeof(COUNT));
    COUNT* count_tmp = m_fator->m_MemData.Get_AllDev_Count();

    if(m_count.Count_Group != 0){
        for(int i = 0;i<m_count.Count_Group;i++){
            int tmp_ID = *((qdata->Buf)+sizeof(HEAD)+sizeof(COUNT)+i*sizeof(int));
            NODE_GRP * grp_find = m_fator->m_MemData.DeviceGrp_map[tmp_ID];
            if(grp_find ==NULL){
                printf("不存在ID 为 %d  的分组节点\n",tmp_ID);
            }
            else{
                m_fator->m_MemData.DeviceGrp_map.erase(tmp_ID);
                printf("删除的设备分组 ID  %d\n",tmp_ID);
                stringstream sql;
                string terminal;
                sql<<"delete from dev_group where ID="<<tmp_ID<<";";
                terminal = sql.str();
                mysql_query(&mysql,terminal.data());

                count_tmp->Count_Group--;
            }
        }
    }
    printf("m_count.Count_Group %d\n",m_count.Count_Group);
    printf("m_count.Count_Device %d\n",m_count.Count_Device);
    if(m_count.Count_Device != 0){
        for(int i =0;i<m_count.Count_Device;i++){
         int tmp_ID = *((qdata->Buf)+sizeof(HEAD)+sizeof(COUNT)+m_count.Count_Group*sizeof(int) + i*sizeof(int));
         NODE* dev_find =  m_fator->m_MemData.Device_map[tmp_ID] ;
         if(dev_find !=NULL){
             m_fator->m_MemData.Device_map.erase(tmp_ID);
             printf("删除的设备 ID  %d\n",tmp_ID);
            stringstream sql;
            string terminal;
            sql<<"delete from dev where ID="<<tmp_ID<<";";
            terminal = sql.str();
            mysql_query(&mysql,terminal.data());
             count_tmp->Count_Device--;
            }
        }
    }

}

void UserloginJob::WriteLogTo_LogServer(char* objname,int type,int obj,int objID)
{
    HT_LOG log;
    memset(&log,0,sizeof(HT_LOG));
    printf("log name strlen is %d\n",strlen(objname));
    memcpy(log.name,objname,strlen(objname));
    log.object = obj;
    log.objectID = objID;
   // log.typegrp =  typegrp;
    log.type = type;
    log.time = GetTime();
    memcpy(log.content,"成功登录管理服务器；IP：192.168.1.149",256);
    printf("log.object %d\n",log.object );
    printf("log.objectID  %d\n",log.objectID);
 //   printf("log.typegrp %d\n",log.typegrp);
    printf("log.time %d\n",log.time);
    printf("log.type %0x\n",log.type);
   // m_fd = m_fator->GetLogSocket();
    printf("go here\n");

    HEAD head;
    head.SysMark = NET_SYSTEM_MASK_HTP;
    head.ModuleMark = NET_MOUDLE_MASK_MCS;
    head.PackType = NET_PACKTYPE_LOG_WRITE;
    head.PackSize = sizeof(HT_LOG)+sizeof(HEAD);
    head.DataSize = sizeof(HT_LOG);
    head.ResultCode = HT_PLATFORM_RESULTCODE_SUCESS;
    head.SessionID = 0;
    char* buff = new char[sizeof(HT_LOG)+sizeof(HEAD)];
    memset(buff,0,sizeof(HT_LOG)+sizeof(HEAD));
    memcpy(buff,&head,sizeof(HEAD));
    memcpy(buff+sizeof(HEAD),&log,sizeof(HT_LOG));
    conn_t* fd = m_fator->GetLogSocket();
    //conn_t* fd = Tcp_Connect("192.168.1.86",4500,NULL,NULL,NULL,1,0);
    if(fd != NULL)
        Tcp_SendMsg(fd,buff,sizeof(HT_LOG)+sizeof(HEAD));
    else
        printf("log sever off line\n");

}

void UserloginJob::Request_Data(int mark,char* data,int result,int sessionID,unsigned int len)
{
    HEAD head;
    head.SysMark = NET_SYSTEM_MASK_HTP;
    head.ModuleMark = NET_MOUDLE_MASK_MCS;
    head.PackType = mark;
    head.PackSize = len+sizeof(HEAD);
    head.DataSize = len;
    head.ResultCode = result;
  //  printf("head.ResultCode  %d\n",result);
  //  printf("head.PackType  %d\n",mark);
    head.SessionID = sessionID;
    char* buff = new char[len+sizeof(HEAD)];
    memcpy(buff,&head,sizeof(HEAD));
    if(data != NULL)
        memcpy(buff+sizeof(HEAD),data,len);
    Push_SendData(buff,m_fd);

}

void UserloginJob::Push_SendData(char* buff,conn_t* m_fd)
{
          m_qSendData = new QueueSendData;
          m_fator->m_queueSendMutex.lock();
          m_qSendData->Send = buff;
          m_qSendData->fd = m_fd;
          m_fator->m_sendaddr.push(m_qSendData);
          m_fator->m_queueSendMutex.unlock();

          if(ObjectFactoy::flag_send)
            sem_post(&(ObjectFactoy::start_chk_send));
}
