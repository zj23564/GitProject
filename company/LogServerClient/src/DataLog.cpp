#include "../include/DataLog.h"
#include "../include/Protocol.h"
#include "../include/Define.h"
#include "../include/log_client_define.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
DataLog::DataLog(char* ip,int port)
{
    //ctor
    memcpy(serverIP,ip,16);
    serverPort = port;
    alllog = NULL;
}

DataLog::~DataLog()
{
    //dtor
}
bool DataLog::NetInit()
{
    HT_NET_Engine_init_nolog(2,1000);
    printf("connect server ip is %s\n",serverIP);
    fd = Tcp_Connect(serverIP,serverPort,GetDataFromLogServer,Event_Net,NULL,1,0);
    if(NULL == fd){
        printf("can not connect server\n");
        return false;
    }
    Tcp_SetContext(fd,this);
    return true;
}
void DataLog::ReqLogTypeObj()
{
    SendDataPkgToServer(NET_PACKTYPE_LOG_GETLOGTYPEOBJ,NULL,0);
}
void DataLog::ReqLogType()
{
    SendDataPkgToServer(NET_PACKTYPE_LOG_GETLOGTYPE,NULL,0);
}
void Event_Net(conn_t *conn, int eventtype, void *context, int error)
{
    printf("net sys event\n");
    DataLog* log = (DataLog*)context;
    switch(eventtype){
        case NET_CONNECT_EVENT:printf("connect event\n");break;
        case NET_CLOSED_EVENT:printf("close event\n");
            log->m_callback(log->GetGuiItem(),NULL,DATA_TO_GUI_COMMAND_LOGSEVERCLOSE);
            Tcp_Close(conn);
            break;
        case NET_RECV_ERROR_EVENT:printf("recv error\n");break;
        case NET_SEND_ERROR_EVENT:printf("send error\n");break;
        case NET_WRITECOMPETE_EVENT:printf("write complete\n");break;
        default:
            break;
    }
}
void GetDataFromLogServer(conn_t *conn, char *buf, int len, void *context)
{
    printf("data log recevied data len is %d\n",len);
    HEAD* hd = (HEAD*)buf;
    printf("sys mark is %0x\n",hd->SysMark);
    if(NET_SYSTEM_MASK_HTP != hd->SysMark){
        printf("illegal data\n");
        return;
    }
     DataLog* log = (DataLog*)context;
    switch(hd->PackType){
        case NET_PACKTYPE_LOG_RESPONSE_QUERY:{   //响应查询日志

            //char* t_alllog = log->GetAllLogAddr();
            log->alllog = new char[len];
            printf("new mem addr is %p\n",log->alllog);
            memset(log->alllog,0,len);
            memcpy(log->alllog,buf,len);
            log->m_callback(log->GetGuiItem(),(void*)log->alllog,DATA_TO_GUI_COMMAND_LOG_DATA);
            break;
        }
        case NET_PACKTYPE_LOG_GETLOGTYPEOBJ:{       //取得日志类型
            printf("GetLogTypeGrp\n");
            log->GetLogTypeObj(buf,len);
            break;
        }
        case NET_PACKTYPE_LOG_GETLOGTYPE:{      //取得日志子类型
            printf("GetLogType\n");
            log->GetLogType(buf,len);
            break;
        }
        case NET_PACKTYPE_LOG_ADDSOURCETYPE:{
            log->GetLogTypeObj(buf,len);
            log->m_callback(log->GetGuiItem(),NULL,DATA_TO_GUI_COMMAND_ADDSOURCETYPE);
            break;
        }
        case NET_PACKTYPE_LOG_ADDLOGTYPE:{
            log->GetLogType(buf,len);
            log->m_callback(log->GetGuiItem(),NULL,DATA_TO_GUI_COMMAND_ADDLOGTYPE);
            break;
        }
        case NET_PACKTYPE_LOG_SREACH_REALTIMELOG:{
            printf("real time log\n");
            HT_LOG_ITEM* ite = new HT_LOG_ITEM;
            memset(ite,0,sizeof(HT_LOG_ITEM));
            memcpy(ite,buf+sizeof(HEAD),sizeof(HT_LOG_ITEM));
            log->realtime_log_vector.push_back(ite);
            log->m_callback(log->GetGuiItem(),(void*)ite,DATA_TO_GUI_COMMAND_REALTIMELOG);
        }
    }
}

void DataLog::GetGuiDataRequest(char* data,int len)
{
    Tcp_SendMsg(fd,data,len);
}

void DataLog::GetLogTypeObj(char*data,int len)      //取得所有日志类型
{
    int num = (len-sizeof(HEAD))/sizeof(LogObjType);
    printf("add num is %d\n",num);
    for(int i = 0;i<num;i++){
        LogObjType* obj = new LogObjType;
        memset(obj,0,sizeof(LogObjType));
        memcpy(obj,data+sizeof(HEAD)+i*sizeof(LogObjType),sizeof(LogObjType));
        printf("type grp %d name is %s\n",i,obj->name);
        LogTypeObj_map[obj->type] = obj;
    }

}
void DataLog::GetLogType(char*data,int len)         //取得所有日志子类
{
    int num = (len-sizeof(HEAD))/sizeof(LogType);
    for(int i = 0;i<num;i++){
        LogType* type = new LogType;
        memset(type,0,sizeof(LogType));
        memcpy(type,data+sizeof(HEAD)+i*sizeof(LogType),sizeof(LogType));
        printf("type %d name is %s\n",i,type->name);
        LogType_map[type->ID] = type;
    }
}


void DataLog::SendDataPkgToServer(int mark,char*data,int len)
{
    HEAD head;
    memset(&head,0,sizeof(HEAD));
    head.SysMark = NET_SYSTEM_MASK_HTP;
    head.ModuleMark = NET_MOUDLE_MASK_LOG;
    head.PackType = mark;
    head.DataSize = len;
    head.PackSize = len+sizeof(HEAD);
    char* buff = new char[sizeof(HEAD)+len];
    memset(buff,0,sizeof(HEAD)+len);
    memcpy(buff,&head,sizeof(HEAD));
    if(NULL != data)
        memcpy(buff+sizeof(HEAD),data,len);
    if(NULL != fd)
        Tcp_SendMsg(fd,buff,head.PackSize);
    else
        m_callback(GetGuiItem(),NULL,DATA_TO_GUI_COMMAND_CONNECTSERVERERROR);
}

