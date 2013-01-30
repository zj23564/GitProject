#include <map>
#include "stdlib.h"
#include "stdio.h"
#include "include/init/ObjectFactoy.h"
#include "include/define/Define.h"
#include "include/data_define/Protocol.h"
#include "include/log/write_log.h"


unsigned long Seccesion = 0;
int log_count = 0;
extern ObjectFactoy *m_fator;

void Event_Sys(conn_t *conn, int eventtype, void *context, int error)
{
    printf("sys event\n");

    switch(eventtype){
        case NET_CONNECT_EVENT:printf("connect event\n");break;
        case NET_CLOSED_EVENT:printf("close event\n");
            if(conn == m_fator->GetLogSocket()){
                    m_fator->SetLogSocket(NULL);
            }
            break;
        case NET_RECV_ERROR_EVENT:printf("recv error\n");break;
        case NET_SEND_ERROR_EVENT:printf("send error\n");break;
        case NET_WRITECOMPETE_EVENT:printf("write complete\n");break;
        default:
            break;
    }
}

void Event_Dev(conn_t *conn, int eventtype, void *context, int error)
{
    printf("device event\n");
}
void NetInit()
{
    HT_NET_Engine_init(8, 1000);

    Tcp_Server_Start(3250,ObjectFactoy::GetData, Event_Sys,NULL, 1);
    Tcp_Server_Start(3300,ObjectFactoy::GetData_Device, Event_Dev,NULL, 0);
}


void Scanf_Timer(int arg)
{
  //  printf("in global scanf time\n");
    /********************定时重连日志服务器，如果已经连接上，则不重连******************/
    conn_t* log_fd = m_fator->GetLogSocket();
    if(NULL == log_fd){
        printf("try to connect log server\n");
        ServerInfo*   log = m_fator->GetLogServerInfo() ;
        conn_t* t_fd = Tcp_Connect(log->m_Addr,log->m_Port,NULL,Event_Sys,NULL,1,0);
        if(t_fd != NULL)
            printf("try to connect log server successful\n");
        m_fator->SetLogSocket(t_fd);
    }

    /****************************************************************************************/

    time_t ti;
    ti = time(NULL);
    LOG_DEVICE* tmp;
    int size = m_fator->Login_device.size();
    int flag = 0;
  //  char* buff = new char[sizeof(HEAD)+sizeof(DEVICELOGOUT_COUNT)+sizeof(DEVICELOGOUT)]
    vector<DEVICELOGOUT*> logout;
    for(m_fator->it_device = m_fator->Login_device.begin();m_fator->it_device != m_fator->Login_device.end();){

        tmp = m_fator->it_device->second;

//        printf("sys time is %d\n",ti);
//        printf("tmp now time is %d\n",tmp->hart_nowtime);
//        printf("sys - nowtime is %d\n",ti-tmp->hart_nowtime);

        if((ti-tmp->hart_nowtime) > 60){
           printf("掉线了\n");
           flag = 1;

           printf("log out device ID  is %d\n",tmp->device->ID);
           m_fator->Change_Device_Status(tmp->device->ID);
           m_fator->Login_device.erase(m_fator->it_device->first);
 //          NetEngine_Server_ePoll_CloseForClient(m_fator->it_device->first);

           DEVICELOGOUT* out = new DEVICELOGOUT;
           out->ID = tmp->device->ID;
           out->m_time = tmp->hart_nowtime;
           logout.push_back(out);
           printf("here\n");
        //   delete tmp->device;
         //  delete tmp;
        }
        else{
            m_fator->it_device++;
        }
    }

        if(flag == 1){

            int j = logout.size();
            char* buff = new char[sizeof(HEAD)+sizeof(DEVICELOGOUT_COUNT)+sizeof(DEVICELOGOUT)*j];
            HEAD head;
            head.SysMark = NET_SYSTEM_MASK_HTP;
            head.ModuleMark = NET_MOUDLE_MASK_MCS;
            head.PackType = NET_PACKTYPE_MCS_NOTICE_DEVICE_ALARM;
            head.PackSize = sizeof(HEAD)+sizeof(DEVICELOGOUT_COUNT)+sizeof(DEVICELOGOUT)*j;
            head.DataSize = sizeof(DEVICELOGOUT_COUNT)+sizeof(DEVICELOGOUT)*j;
            memcpy(buff,&head,sizeof(HEAD));
            DEVICELOGOUT_COUNT out_count;
            out_count.logout_count = j;
            memcpy(buff+sizeof(HEAD),&out_count,sizeof(DEVICELOGOUT_COUNT));
            for(int i = 0;i<j;i++){
                memcpy(buff+sizeof(HEAD)+sizeof(DEVICELOGOUT_COUNT)+sizeof(DEVICELOGOUT)*i,logout[i],sizeof(DEVICELOGOUT));
                DEVICELOGOUT* p = logout[i];
                printf("here two\n");
              //  delete p;
            }

            Tcp_SendMsg(m_fator->GetMctSocket(),buff,sizeof(HEAD)+sizeof(DEVICELOGOUT_COUNT)+sizeof(DEVICELOGOUT)*j);
            Tcp_SendMsg(m_fator->GetLogSocket(),buff,sizeof(HEAD)+sizeof(DEVICELOGOUT_COUNT)+sizeof(DEVICELOGOUT)*j);
        }
        else{
            //printf("Device is of all normal\n");
        }
}
