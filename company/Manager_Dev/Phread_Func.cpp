#include <iostream>
#include "device_register.h"


#include "include/init/ObjectFactoy.h"
#include <signal.h>
#include <sys/time.h>
extern ObjectFactoy *m_fator;
extern void Scanf_Timer(int arg);

void* ScanOnlineDevice(void*arg)
{
    printf("init timer\n");

     signal(SIGALRM,Scanf_Timer);

    struct itimerval tick;
    memset(&tick,0,sizeof(tick));
    tick.it_value.tv_sec = 30;
    tick.it_value.tv_usec = 0;

    tick.it_interval.tv_sec = 30;
    tick.it_interval.tv_usec = 0;

    int res = setitimer(ITIMER_REAL, &tick, NULL);
    if(res ==0 ){
        printf("timer set OK\n");
    }
    sem_wait(&(ObjectFactoy::sem_scanf));
}

//设备注册线程开启，处理设备发送来的数据和请求，设备有关任务全部由此开始
void* Device_reg(void* arg)
{
  printf("run device register\n");
  while(1)
    ((ObjectFactoy *)arg)->DealqueueDeviceData();
}
//管理设备发送给本服务器的数据队列
void* Manager_Device_queue(void* arg)
{

    while(1){
    //    printf("run Manager_Device_queue()\n");
    sem_wait(&(ObjectFactoy::sem_device));
    //printf("is in Manger_queue\n");
    ObjectFactoy *m_que = (ObjectFactoy *)arg;

    sem_wait(&(ObjectFactoy::start_device));
    m_que->flag_device = 0;
    sem_post(&ObjectFactoy::sem_deal_device);

    }

}


//管理各个服务器发送给本服务器的数据的队列
void* Manager_queue(void* arg)
{
  while(1){
    sem_wait(&(ObjectFactoy::sem));
    ObjectFactoy *m_que = (ObjectFactoy *)arg;
    sem_wait(&(ObjectFactoy::start));
    m_que->flag = 0;
    sem_post(&ObjectFactoy::sem_deal);
  }
}

//管理发送队列的线程
void* ManagerSend_queue(void* arg)
{
    while(1){
    sem_wait(&(ObjectFactoy::sem_send));
   // printf("is in Manger_Sendqueue\n");
    ObjectFactoy *m_que = (ObjectFactoy *)arg;

    sem_wait(&(ObjectFactoy::start_chk_send));
    m_que->flag_send = 0;
    sem_post(&ObjectFactoy::sem_deal_send);
   // printf("post sem_deal_send\n");
  }
}


//循环从发送队列中拿出数据，处理发送任务
void* Run_send(void* arg)
{
    ObjectFactoy *m_que = (ObjectFactoy *)arg;
    while(1){
  //      printf("run send job\n");
        m_fator->GetJob_Send();
    }
}
