
#include "../Define.h"
#include "../Protocol.h"
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>
#include <queue>
#include "../include/log_define.h"
#include "../netlib/HT_NET_Engine.h"
#include "../USERDEVDATA.h"
#include "../include/log_hub.h"
#include <vector>
#include <pthread.h>
using namespace std;

extern queue<DB_MSG*> db_queue;
extern queue<DB_MSG*>  hub_queue;
extern USERDEVDATA* user;
extern sem_t sem_realTime;
extern int sem_hubqueue_flag;

vector<int> realtime_log_fd;        //申请实时日志请求的连接套接字
extern pthread_mutex_t mutex_RealTimeLogSocket_vector;
void *hub_thread_fun(void *arg)
{
    printf("in hub_thread_fun\n");
    while(1){
        while(hub_queue.size() != 0){
            DB_MSG *dbmsg = hub_queue.front();
            sem_hubqueue_flag = 0;
            Deal_hub_Switch((void*)dbmsg);
            printf("ready to deal hubqueue\n");
            hub_queue.pop();
            delete [] (char*)(dbmsg->msg);
            delete dbmsg;
        }
        sem_hubqueue_flag = 1;
        sem_wait(&sem_realTime);
    }

    return NULL;
}

int Deal_hub_Switch(void*msg)
{
    pthread_mutex_lock(&mutex_RealTimeLogSocket_vector);
    for(int i = 0;i<realtime_log_fd.size();i++){
            char* send = Pkg_reallog(msg);
            if(send != NULL){
                Tcp_SendMsg((conn_t*)realtime_log_fd.at(i),send,((HEAD*)send)->PackSize);
                 printf("send log to request\n");
            }
            else
                printf("send message is NULL don't send\n");

    }
    pthread_mutex_unlock(&mutex_RealTimeLogSocket_vector);
}

char* Pkg_reallog(void*msg)
{
    if(msg != NULL){
        DB_MSG *dbmsg = (DB_MSG*)msg;
        HT_LOG*  log= (HT_LOG*)(((char*)(dbmsg->msg))+sizeof(HEAD));
        HT_LOG_ITEM ite;
        memset(&ite,0,sizeof(HT_LOG_ITEM));
        ite.time = log->time;
        memcpy(ite.context,log->content,256);

        LogObjType* t_objType = user->LogTypeObj_map[log->object];
        memcpy(ite.objtype,t_objType->name,32);

        LogType * t_type = user->LogType_map[log->type];
        memcpy(ite.type,t_type->name,64);
        if(log->object == 1){
            USERINFO*  m_usr = user->usr_map[log->objectID];
            printf("**********************\n");
            if(m_usr != NULL)
                memcpy(ite.obj,m_usr->Name,64);
            else
                printf("there have not the user object\n");

        }
        else{
            DEVICE* dev = user->dev_map[log->objectID];
            if(dev != NULL)
                memcpy(ite.obj,dev->name,strlen(dev->name));
            else
                printf("can not find the dev obj\n");
        }
        memcpy(ite.context,log->content,256);

        HEAD t_head;
        t_head.SysMark = NET_SYSTEM_MASK_HTP;
        t_head.ModuleMark = NET_MOUDLE_MASK_LOG;
        t_head.PackType = NET_PACKTYPE_LOG_SREACH_REALTIMELOG;
        t_head.PackSize = sizeof(HEAD)+sizeof(HT_LOG_ITEM);
        t_head.DataSize = t_head.PackSize-sizeof(HEAD);
        char* buff = new char[t_head.PackSize];
        memset(buff,0,t_head.PackSize);
        memcpy(buff,&t_head,sizeof(HEAD));
        memcpy(buff+sizeof(HEAD),&ite,sizeof(HT_LOG_ITEM));
        return buff;
    }
    else
        printf("msg is null\n");
        return NULL;
}
