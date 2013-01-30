#include <iostream>
#include "device_register.h"
#include "GlobalFunc.h"
#include "include/init/ObjectFactoy.h"
#include "include/log/write_log.h"
#include "mysql/mysql.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
extern unsigned long Seccesion;
MYSQL mysql;
ObjectFactoy *m_fator;

//Map<unsigned long,string>log_map;

int main(int argc,char**argv)
{
    if(argv[1]  == NULL){
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
    else if(strcmp(argv[1],"debug") != 0){
        printf("command error\n");
        return 0;
    }

    m_fator = ObjectFactoy::GetFactoryInstance();

    sem_init(&(ObjectFactoy::sem),0,0);
    sem_init(&(ObjectFactoy::start),0,0);
    sem_init(&(ObjectFactoy::sem_deal),0,0);

    sem_init(&(ObjectFactoy::sem_send),0,0);
    sem_init(&(ObjectFactoy::start_chk_send),0,0);
    sem_init(&(ObjectFactoy::sem_deal_send),0,0);

    sem_init(&(ObjectFactoy::sem_device),0,0);
    sem_init(&(ObjectFactoy::start_device),0,0);
    sem_init(&(ObjectFactoy::sem_deal_device),0,0);
    sem_init(&(ObjectFactoy::sem_scanf),0,0);

    mysql_init(&mysql);

    pthread_t manager_queue;
    pthread_t manager_Sendqueue;
    pthread_t run_send;
    pthread_t device_reg;
    pthread_t manager_Devicequeue;
    pthread_t timer;        //定时扫描在线设备中有的设备，用于检测是否长时间没受到设备心跳包，判断是否掉线

    pthread_create(&manager_queue,NULL,Manager_queue,(void*)m_fator);
    pthread_create(&manager_Sendqueue,NULL,ManagerSend_queue,(void*)m_fator);
    pthread_create(&run_send,NULL,Run_send,(void*)m_fator);
    pthread_create(&timer,NULL,ScanOnlineDevice,(void*)m_fator);
    pthread_create(&manager_Devicequeue,NULL,Manager_Device_queue,(void*)m_fator);

    char* localIP = GetLocalIP();
    mysql_real_connect(&mysql,localIP,"root","haotel","powerManager",0,NULL,0);
    mysql_set_character_set(&mysql,"UTF8");
    delete []localIP;

    m_fator->m_MemData.Get_Device_Block();
    m_fator->m_MemData.Get_User_Block();

    NetInit();
            //运行和设备进行数据交流的主线程
    pthread_create(&device_reg,NULL,Device_reg,(void*)m_fator);


         //   运行与各个服务器之间进行数据交互的主线程，目前就这个线程就是程序的主线程
    while(1){
        m_fator->DealqueueData();
    }


    return 0;
}
