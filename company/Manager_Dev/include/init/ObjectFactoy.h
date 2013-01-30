#ifndef OBJECTFACTOY_H_INCLUDED
#define OBJECTFACTOY_H_INCLUDED

#include <queue>
#include <semaphore.h>
#include "../data_define/Data_Define.h"
#include "../ThreadPool/Mutex.h"
#include "../ThreadPool/ThreadManage.h"
#include "../../Device_Job.h"
#include "Mem_Data.h"
#include "../../HT_NET_Engine.h"
#include "../devLogin/devLoginManager.h"
using namespace std;




class ObjectFactoy
{
    public :
      ObjectFactoy();
      ~ObjectFactoy();
      unsigned long         PacketType;
      static void  GetData(conn_t *conn, char *buf, int len, void *context);
      static void  GetData_Device(conn_t *conn, char *buf, int len, void *context);
      static ObjectFactoy * GetFactoryInstance();
      CMutex GetqueueMutex(){return m_queueMutex;}
      CThreadManage         m_ThreadMag;
      CThreadManage         m_ThreadSend;
      CThreadManage         m_ThreadRegister;
      MEM_DATA                m_MemData;
      DEVMANAGER           m_devManager;



       int                  	GetQueueSize();
      void                  	DealqueueData();
      void                   DealqueueDeviceData();
      CJob*                 GetJobObject(QueueData * Data);
      void                	GetJob_Send();    //处理发送队列里面的数据
      void 					Gettime(void);			//取得系统当前时间
      void 					ReadXml();				//读取xml请求命令文件
      void*					DealXml(void *arg);	//处理XML数据
      int						Device_Register(void);	//设备注册函数
      int 					Ans_Xml(DEVICE_DATA* data);		//解析xml的标签内容
      int 					start_epoll(void);

      void                  Change_Device_Status(int ID);      //检测到设备掉线了，将内存中设备数据更改为离线状态
      void                  Deal_Device_LineOff(void);              //将离线设备信息发送给主控端和报警服务器

      conn_t *                     GetMctSocket() {return fd_mct;}
      conn_t *                     GetTVWallSocket() {return fd_tvwall;}
      conn_t *                     GetAlarmSocket() {return fd_alarm;}
      conn_t *                     GetLogSocket() {return fd_log;}
      conn_t *                     GetStreamSocket() {return fd_stream;}
      conn_t *                     GetStorageSocket() {return fd_storage;}

        void                              SetLogSocket(conn_t* fd){fd_log = fd;}
        void                              SetMctSocket(conn_t* fd){fd_mct = fd;}
        void                              SetTVWallSocket(conn_t* fd){fd_tvwall = fd;}
        void                              SetAlarmSocket(conn_t* fd){fd_alarm = fd;}
        void                              SetStreamSocket(conn_t* fd){fd_stream = fd;}
        void                              SetStorageSocket(conn_t* fd){fd_storage = fd;}


      void                      SetTVWallServerInfo(char* info) { memcpy(&m_TVWallServer,info,sizeof(ServerInfo));}
      void                      SetAlarmServerInfo(char* info) {memcpy(&m_AlarmServer,info,sizeof(ServerInfo));}
      void                      SetLogServerInfo(char* info) {memcpy(&m_LogServer,info,sizeof(ServerInfo));}
      void                      SetStreamServerInfo(char* info) {memcpy(&m_StreamServer,info,sizeof(ServerInfo));}
      void                      SetStorageServerInfo(char* info) {memcpy(&m_StorageServer,info,sizeof(ServerInfo));}

      ServerInfo*                      GetTVWallServerInfo() {return &m_TVWallServer;}
      ServerInfo*                      GetAlarmServerInfo() {return &m_AlarmServer;}
      ServerInfo*                      GetLogServerInfo() {return &m_LogServer;}
      ServerInfo*                      GetStreamServerInfo() {return &m_StreamServer;}
      ServerInfo*                      GetStorageServerInfo() {return &m_StorageServer;}



           //SendData*          Get_All_Device(){return All_Device;}

    //void Get_queue_size(){queue_size = m_queue.size();}
      static sem_t  sem;
      static sem_t  sem_deal;
      static sem_t start;
      static sem_t  start_chk_send;
      static sem_t  sem_deal_send;
      static sem_t sem_send;
      static sem_t sem_scanf;

      static sem_t  start_device;
      static sem_t  sem_deal_device;
      static sem_t sem_device;

      static CMutex               m_sMutex;         //用于使用mysql变量的互斥量
      static CMutex               m_queueMutex;
      static CMutex               m_queueSendMutex;
      static queue<QueueSendData*>    m_sendaddr;

       int queue_size;
       int login_user_sid;
       static bool                       flag;
       static bool                       flag_send;
       static bool                       flag_device;


        char read_buff1[1024];
        char read_buff2[1024];
        char read_buff3[1024];
        char read_buff4[1024];
        char timebuff[1024];
       // map<int,MAP_USER_NAME*> login_user;         //sessionID对应登录用户
       map<int,USERINFO*> login_user;
        map<int,MAP_USER_NAME*>::iterator it_login;

        map<int,LOG_DEVICE*> Login_device;        //在线设备的map表   套接口对应
        map<int,LOG_DEVICE*>::iterator it_device;

        MSSINFO  mssinfo;
    private :
      static queue<QueueData* >    m_queue;  //收到的数据的队列
             //数据经过解析处理后需要回馈的数据的地址指针队列，用于发送队列

      static queue<DEVICE_DATA* >    m_device_data;         //收到的设备数据的队列
      static DEVICE_DATA*                    device_data;
      static ObjectFactoy         * p_Factory;
      static QueueData*            m_qData;


      conn_t * fd_mct;       //上线的主控端套接口
      conn_t * fd_alarm;    //上线的报警服务器套接口
      conn_t * fd_log;       //上线的log server套接口
      conn_t * fd_storage;    //存储模块套接口
      conn_t * fd_stream;       //流媒体模块套接口
      conn_t * fd_tvwall;       //tv wall

    ServerInfo m_AlarmServer;
    ServerInfo m_StreamServer;
    ServerInfo m_LogServer;
    ServerInfo m_TVWallServer;
    ServerInfo m_StorageServer;




    //  SendData*  All_Device;
      };



#endif // OBJECTFACTOY_H_INCLUDED
