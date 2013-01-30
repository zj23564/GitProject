
#include "../Protocol.h"
#include "../Define.h"
#include "../include/log_define.h"
#include "../netlib/HT_NET_Engine.h"
#include <stdio.h>
#include <queue>
#include <semaphore.h>
#include<pthread.h>
using namespace std;
queue<DB_MSG*> db_queue;
queue<DB_MSG*>  hub_queue;
pthread_mutex_t mutex_RealTimeLogSocket_vector;
int sem_dbqueue_flag = 0;
int sem_hubqueue_flag = 0;
extern sem_t sem;
extern sem_t sem_realTime;

extern vector<int> realtime_log_fd;        //申请实时日志请求的连接套接字
void  GetData(conn_t *conn, char *buf, int len, void *context)
{
    printf("received data len is %d\n",len);
    HEAD* head = (HEAD*)buf;
    if(NET_SYSTEM_MASK_HTP != head->SysMark){
        printf("Illegal data\n");
        return;
    }

    char *htlog = new char[len];     //to sql
    char *hub_htlog = new char[len];    //to timing log
    memcpy(htlog, buf, len);
    memcpy(hub_htlog, buf,len);
    DB_MSG *dbmsg =  new DB_MSG;        //to sql
    DB_MSG *hubmsg =  new DB_MSG;   //to timing log
    dbmsg->msg = (void*)htlog;
    dbmsg->sid = (int)conn;
    dbmsg->datalen = len;
    memcpy(hubmsg,dbmsg,sizeof(DB_MSG));
    hubmsg->msg = (void*)hub_htlog;

    db_queue.push(dbmsg);
    if(sem_dbqueue_flag == 1)
        sem_post(&sem);

    if((NET_PACKTYPE_LOG_REQUSE_QUERY != head->PackType)&&\
       (NET_PACKTYPE_LOG_SREACH_REALTIMELOG != head->PackType)&&\
       (NET_PACKTYPE_LOG_GETLOGTYPEOBJ != head->PackType)&&\
       (NET_PACKTYPE_LOG_GETLOGTYPE != head->PackType)&&\
       (NET_PACKTYPE_LOG_ADDSOURCETYPE != head->PackType)&&\
       (NET_PACKTYPE_LOG_ADDLOGTYPE != head->PackType)){
        hub_queue.push(hubmsg);
        printf("push data to hub queue\n");
        if(sem_hubqueue_flag == 1)
            sem_post(&sem_realTime);
    }



}
void Delete_RealTimeLogSocket(void* fd)
{
    conn_t* m_fd = (conn_t*)fd;
    vector<int>::iterator item;
    pthread_mutex_lock(&mutex_RealTimeLogSocket_vector);
    for(item=realtime_log_fd.begin();item!=realtime_log_fd.end();item++){
        conn_t* v_fd = (conn_t*)(*item);
        if(v_fd == m_fd){
            printf("delete one read time log socket\n");
            realtime_log_fd.erase(item);
            break;
        }
    }
    pthread_mutex_unlock(&mutex_RealTimeLogSocket_vector);
    Tcp_Close(m_fd);
}

void Event_Sys(conn_t *conn, int eventtype, void *context, int error)
{
    printf("sys event\n");
    switch(eventtype){
        case NET_CONNECT_EVENT:printf("connect event\n");break;
        case NET_CLOSED_EVENT:printf("close event\n");Delete_RealTimeLogSocket(conn);break;
        case NET_RECV_ERROR_EVENT:printf("recv error\n");Delete_RealTimeLogSocket(conn);break;
        case NET_SEND_ERROR_EVENT:printf("send error\n");Delete_RealTimeLogSocket(conn);break;
        case NET_WRITECOMPETE_EVENT:printf("write complete\n");break;
        default:
            break;
    }

}



void NetInit()
{
    HT_NET_Engine_init(4, 1000);
    Tcp_Server_Start(4500,GetData, Event_Sys,NULL, 1);
    pthread_mutex_init(&mutex_RealTimeLogSocket_vector,NULL);
}
