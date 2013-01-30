
//#include "Device_Job.h"
//#include "Device_Data.h"
#include "include/init/ObjectFactoy.h"
extern ObjectFactoy *m_fator;
Device_Job::Device_Job(int flag,DEVICE_DATA* data)
{
    m_fd = data->fd;
    m_len = data->len;
    m_flag = flag;
    m_data = data;
}

Device_Job::~Device_Job()
{

    //printf("delete Device_job\n");
    delete [] m_data->buff;
    delete m_data;

}

void Device_Job::Run(void * jobData)
{
//    printf("device run ()\n");
  //  printf("m_flag is %d\n",m_flag);
    //DEVICE_DATA* job = (DEVICE_DATA*)jobData;
    switch(m_flag)
    {
        case 1://查询注册
            {
                printf("查询注册\n");
                Tcp_SendMsg(m_fd,m_fator->read_buff1,512);
                break;
            }
         case 2://注册
            {
               printf("注册\n");
                Tcp_SendMsg(m_fd,m_fator->read_buff2,512);
                break;
            }
          case 3://心跳包
            {
            m_fator->Gettime();
            printf("心跳包\n");

            //获取这次心跳包的时间，修改在线设备的时间
            LOG_DEVICE* tmp = m_fator->Login_device[(int)m_fd];
            printf("m_sock is  %d\n",m_fd);
            if(tmp != NULL){
                time_t ti;
                ti = time(NULL);
                tmp->hart_nowtime = ti;
                Tcp_SendMsg(m_fd,m_fator->timebuff,512);
            }
            else{
                printf("No such log_device in log map\n");
                return;
            }
       //     printf("heartbeat is \n*********\%s\n*************\n",m_fator->timebuff);

                break;
            }
          case 4://报警
            {
                break;
            }
          case 5://状态回馈
            {
                break;
            }
          default:
                break;
    }
}
