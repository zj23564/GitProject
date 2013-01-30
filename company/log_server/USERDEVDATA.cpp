#include "USERDEVDATA.h"
#include "Protocol.h"
#include "Define.h"
#include "mysql.h"
#include "include/log_db.h"
extern MYSQL *db_mysql;
USERDEVDATA::USERDEVDATA(char* McsIp)
{
    //ctor
    memset(mscIP,0,16);
    memcpy(mscIP,McsIp,16);
    GetLogTypeObjFromSql();
    GetLogTypeFromSql();
    printf("connect mcs ip is %s\n",mscIP);
    fd = Tcp_Connect(mscIP,3250,ReceviedData,UserDevDataEvent,NULL,1,0);
    if(fd == NULL){
        printf("manager closed\n log sever run error\n");
        return;
    }
    McsDataInit();
}

USERDEVDATA::~USERDEVDATA()
{
    //dtor
}

void USERDEVDATA::McsDataInit()
{
    //clear dev user map

    map<int,USERINFO*>::iterator item_user;
    map<int,DEVICE*>::iterator item_dev;
    map<int,DEVICE_CHANNEL*>::iterator item_chn;
    for(item_user = usr_map.begin();item_user!= usr_map.end();item_user++){
        USERINFO* usr = item_user->second;
        if(usr!=NULL)
            delete usr;
    }
    usr_map.clear();
    for(item_dev = dev_map.begin();item_dev!= dev_map.end();item_dev++){
        DEVICE* dev = item_dev->second;
        if(dev!= NULL)
            delete dev;
    }
    dev_map.clear();
    for(item_chn = channel_map.begin();item_chn!= channel_map.end();item_chn++){
        DEVICE_CHANNEL* chn = item_chn->second;
        if(chn != NULL)
            delete chn;
    }
    channel_map.clear();

    //data init
    Tcp_SetContext(fd, this);
    ServerInfo logserver;
    char* localIP = GetLocalIP();
    memcpy(logserver.m_Addr,localIP,16);
    delete [] localIP;
    logserver.m_Port = 4500;
    logserver.m_Reserve = NET_MOUDLE_MASK_LOG;
    Request_To_MCS(NET_PACKTYPE_MCS_REQUSET_REGMOUDLE,(char*)&logserver,sizeof(ServerInfo));
    Request_To_MCS(NET_PACKTYPE_MCS_REQUEST_DEVICETREE,NULL,0);
    Request_To_MCS(NET_PACKTYPE_MCS_RESPONSEUSERS,NULL,0);
}

void USERDEVDATA::ReConnect_Mcs()
{
    while(fd == NULL){
        printf("try to reconnect to manager server\n");
        fd = Tcp_Connect(mscIP,3250,ReceviedData,UserDevDataEvent,NULL,1,0);
        if(fd == NULL){
            printf("manager closed\n log sever run error\n");
        }
        sleep(1);
    }
    printf("reconnect to manager server successful\n");
    McsDataInit();
}
void UserDevDataEvent(conn_t *conn, int eventtype, void *context, int error)
{
    USERDEVDATA* usr = (USERDEVDATA*)context;
    switch(eventtype){
        case NET_CONNECT_EVENT:printf("connect event\n");break;
        case NET_CLOSED_EVENT:{
            printf("close event\n");
            Tcp_Close(conn);
            usr->SetMcsfdNULL();
            usr->ReConnect_Mcs();
            break;
        }
        case NET_RECV_ERROR_EVENT:printf("recv error\n");break;
        case NET_SEND_ERROR_EVENT:printf("send error\n");break;
        case NET_WRITECOMPETE_EVENT:printf("write complete\n");break;
        default:
            break;
    }
}
void ReceviedData(conn_t *conn, char *buf, int len, void *context) //USERDEVDATA RECEIVE DATA FUNC
{
         if(NULL == buf){
            printf("The server has disconnected\n");
            return;
        }
        HEAD *head = (HEAD*)buf;
        if(head->SysMark==NET_SYSTEM_MASK_HTP){
            switch(head->PackType){
                case NET_PACKTYPE_MCS_RESPONSE_DEVICETREE:
                {
                    printf("recevied devs data\n");
                    USERDEVDATA* dev = (USERDEVDATA*)context;
                    dev->GetDevData(buf+sizeof(HEAD)+sizeof(MSSINFO));
                    break;
                }
                case NET_PACKTYPE_MCS_RESPONSEUSERS:
                {
                    printf("recevied users data\n");
                    USERDEVDATA* usr = (USERDEVDATA*)context;
                    usr->GetUserData(buf+sizeof(HEAD));
                    break;
                }
            }
        }
}

void USERDEVDATA::GetDevData(char* data)
{
    printf("get device data\n");
    COUNT cnt;
    memcpy(&cnt,data,sizeof(COUNT));
    for(int i = 0;i<cnt.Count_Device;i++){
        DEVICE* dev = new DEVICE;
        memset(dev,0,sizeof(DEVICE));
        memcpy(dev,data+sizeof(COUNT)+sizeof(DEVICE_GRP)*cnt.Count_Group+i*sizeof(DEVICE),sizeof(DEVICE));
        dev_map[dev->ID] = dev;
    }
    for(int i = 0;i<cnt.Count_Channel;i++){
        DEVICE_CHANNEL* chn = new DEVICE_CHANNEL;
        memset(chn,0,sizeof(DEVICE_CHANNEL));
        memcpy(chn,data+sizeof(COUNT)+sizeof(DEVICE_GRP)*cnt.Count_Group+cnt.Count_Device*sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),sizeof(DEVICE_CHANNEL));
        channel_map[chn->ID] = chn;
    }
}
void USERDEVDATA::GetUserData(char* data)
{
    printf("get user data\n");
    USERCOUNT cnt;
    memcpy(&cnt,data,sizeof(USERCOUNT));
    for(int i = 0;i<cnt.Count_User;i++){
        USERINFO* usr = new USERINFO;
        memset(usr,0,sizeof(USERINFO));
        memcpy(usr,data+sizeof(USERCOUNT)+i*sizeof(USERINFO),sizeof(USERINFO));
        usr_map[usr->ID] = usr;
    }
}

void USERDEVDATA::Request_To_MCS(int mark,char* data,int data_len)
{
        char* buff = NULL;
        int len = 0;
        HEAD head;
        head.SysMark = NET_SYSTEM_MASK_HTP;
        head.ModuleMark = NET_MOUDLE_MASK_LOG;

        head.PackType = mark;
        head.SessionID = 1;

        len = sizeof(HEAD)+data_len;
        buff = new char[len];
        memcpy(buff,&head,sizeof(HEAD));

        if(data != NULL){
            memcpy(buff+sizeof(HEAD),data,data_len);
        }
        printf("send buff len is  %d\n",len);
        Tcp_SendMsg(fd,buff,len);
        delete [] buff;
}

void USERDEVDATA::GetLogTypeObjFromSql()
{
    mysql_query(db_mysql,"select * from logobj;");
    MYSQL_RES *res = mysql_store_result(db_mysql);
    int rowcount = mysql_num_rows(res);
    MYSQL_ROW row = mysql_fetch_row(res);

    for(int i = 0;i<rowcount;i++){
        LogObjType* objType = new LogObjType;
        memset(objType,0,sizeof(LogObjType));

        objType->ID = atoi(row[0]);
        objType->type = atoi(row[1]);
        memcpy(objType->name,row[2],strlen(row[2]));
        LogTypeObj_map[objType->type] = objType;
      //  printf("(objType+i)->name %s\n",objType->name);
        row = mysql_fetch_row(res);
    }
     mysql_free_result(res);
}
void USERDEVDATA::GetLogTypeFromSql()
{

    mysql_query(db_mysql,"select * from logtype;");
    MYSQL_RES *res = mysql_store_result(db_mysql);
    int rowcount = mysql_num_rows(res);
    printf("rowcount = %d\n",rowcount);
    MYSQL_ROW row = mysql_fetch_row(res);

    for(int i = 0;i<rowcount;i++){
        LogType* type = new LogType;
        memset(type,0,sizeof(LogType));
        type->ID = atoi(row[0]);
        printf("type ID is %d\n",type->ID);
     //   type->PID = atoi(row[1]);
        type->type_obj = atoi(row[4]);
        memcpy(type->name,row[3],strlen(row[3]));
    //    printf("type type_obj is %d\n",type->type_obj);
        LogType_map[type->ID] = type;
        row = mysql_fetch_row(res);
    }
    mysql_free_result(res);

}
