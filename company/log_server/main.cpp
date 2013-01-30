#include <iostream>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <pthread.h>

#include "include/log_define.h"
#include "include/log_db.h"
#include "include/log_hub.h"
#include "Define.h"
#include "Protocol.h"
#include "include/toolfuncdefine.h"
#include "include/log_db.h"
#include <semaphore.h>
#include "USERDEVDATA.h"
using namespace std;


//void realtime_login(int sid, TcpConnection *tcpconn)
//{
//    log_hub_addclient(sid);
//}
//void realtime_recv(int sid, char *buf, int len, void *context)
//{
//
//    printf("%s: realtime add the sid =%d\n",__FILE__,sid);
//
//}
//void realtime_logout(int sid, void *context)
//{
//    printf("realtime logout the sid =%d\n",sid);
//    log_hub_removeclient(sid);
//}
sem_t sem;
sem_t sem_realTime;
USERDEVDATA* user = NULL;
int main(int argc,char** argv)
{

    if(strcmp(argv[1] ,"debug") != 0){
        pid_t pid ;

        if(pid = fork()){
                exit(0);
        }
        else if(pid < 0)
            exit(1);
        setsid();


        if(pid = fork()){
                exit(0);
        }
        else if(pid < 0)
            exit(1);


        for(int i = 0;i<sysconf(_SC_OPEN_MAX);i++)
            close(i);
    }


    sem_init(&sem,0,0);
    sem_init(&sem_realTime,0,0);
    init_db();
    NetInit();
    if(strcmp(argv[1] ,"debug") == 0)
        user = new USERDEVDATA(argv[2]);
    else
        user = new USERDEVDATA(argv[1]);
    pthread_t deal_dbqueue;
    pthread_create(&deal_dbqueue,NULL,db_thread_fun,NULL);
    pthread_t deal_hubqueue;
    pthread_create(&deal_hubqueue,NULL,hub_thread_fun,NULL);

    getchar();

    return 0;
}

