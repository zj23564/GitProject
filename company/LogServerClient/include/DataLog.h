#ifndef DATALOG_H
#define DATALOG_H
#include "HT_NET_Engine.h"
#include <map>
#include <stdio.h>
#include <vector>
#include <string.h>
#include "LogData_Define.h"
using namespace std;

typedef void (*CallBackFun)(void *gui,void* data,int command);

void GetDataFromLogServer(conn_t *conn, char *buf, int len, void *context);
void Event_Net(conn_t *conn, int eventtype, void *context, int error);
class DataLog
{
    public:
        DataLog(char* ip,int port);
        virtual ~DataLog();


        //初始化的时候需要启动的函数
        bool NetInit();
//        void SetServerIP(char*ip){memcpy(serverIP,ip,16);}
//        void SetServerPort(int port){serverPort = port;}
        void ReqLogTypeObj();
        void ReqLogType();

/************************************************************/
        void setContext(void *context){m_context = context;}
        void setCallback(CallBackFun callback){m_callback = callback;}
        CallBackFun m_callback; //数据进入界面的总回调函数
/***********************界面请求数据函数*****************************************/
        //功能函数
        void GetGuiDataRequest(char* data,int len);   //界面的网络数据请求
/***********************************************************/
        void GetLogTypeObj(char*data,int len);      //取得所有日志类型  //增加新日志源类型同样适用
        void GetLogType(char*data,int len);         //取得所有日志子类型//增加新日志类型同样适用

//        void GetNewLogTypeObj(char*data,int len);      //取得新增日志类型
//        void GetNewLogType(char*data,int len);         //取得新增日志子类型


        char* GetAllLogAddr(){return alllog;}       //取得所有日志的内存起始地址
        void* GetGuiItem(){return m_context;}       //取得界面对象

        map<int,LogObjType*> LogTypeObj_map;
        map<int,LogType*> LogType_map;
        vector<HT_LOG_ITEM*>  realtime_log_vector;      //实时日志存储列表

        void SendDataPkgToServer(int mark,char*data,int len);

/*************************销毁资源**********************************/
        void FreeAllLogData(){
            if(alllog!=NULL){
                printf("delete mem addr is %p\n",alllog);
                delete [] alllog;
                alllog = NULL;
            }
            else{
                printf("alllog is NULL\n");
            }
        }
        char* alllog;

    protected:
    private:

        void *m_context;
        conn_t *fd;


        LogObjType* all_typeobj;
        LogType*    all_type;
        char serverIP[16];
        int serverPort;



};

#endif // DATALOG_H
