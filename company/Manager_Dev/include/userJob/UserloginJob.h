#ifndef USERLOGINJOB_H
#define USERLOGINJOB_H

#include "../ThreadPool/Job.h"
#include "../data_define/Protocol.h"
#include "../data_define/Data_Define.h"
#include "../define/Define.h"
#include "stdio.h"
#include <map>
#include "mysql/mysql.h"
#include "../ThreadPool/Mutex.h"
#include "../init/ObjectFactoy.h"



class UserloginJob : public CJob
{
    public:
        UserloginJob();
        UserloginJob(int sessionID,conn_t* fd);
        //void Get_power(char mpower,unsigned long RHT){m_power = mpower;m_right = RHT;}
        virtual ~UserloginJob();

        void Run(void * jobData);
        void ServerLogin();


        int GetTime();      //get unix time

        void AllUser();
        void AddUser();
        void ModifyUser();
        void DelUser();
        void MCS_USER(unsigned long packType);
        void MCS(unsigned long packType);
        void USER(unsigned long packType);
        int Check_User();      //用户帐号和密码验证
        void User_Login();          //用户登录回复
        void Query_Power();
        void Request_Logout();          //用户退出
        void Modify_passwd();           //修改密码
        void AllUser_Block();
        void Request_StreamTree();
        void Request_ServerInfo();
// write log to log server
        void WriteLogTo_LogServer(char* objname,int type,int obj,int objID);

//设备
        void Add_Device();
        void Change_Device();
        void Del_Device();
        void Del_DeviceGrp();   //删除设备分组
        void Request_Device();
        void Request_All_Device();
        void Request_DeviceStatus();
//设备组
        void Add_DeviceGroup();
        void Change_DeviceGroup();

//power
        void Requset_PowerTree();

        void Push_SendData(char* buff,conn_t* fd);       //将处理后的数据放入工厂发送数据队列的方法

        void Request_Data(int mark,char* data,int result,int sessionID,unsigned int len);        //回复数据函数

        static int session_ID;
    protected:
    private:

       // char * m_UserIP;
       conn_t* m_fd;
 //      int m_sendlen;       //发送数据的长度

        char m_power;
        unsigned int User_cout;     //记录符合用户权限的节点数目
        unsigned long m_right;
        char * AllDeviceBuff;
        QueueData* qdata;
         SendData*  send_info;          //存放的是用户权限控制下的设备节点起始地址和数据长度
        QueueSendData* m_qSendData;


        unsigned long Sysmark;
        unsigned long nModuleType;
        unsigned long packType;
        int m_sessionID;
        //unsigned long node_num;
};

#endif // USERLOGINJOB_H
