#include "../include/log_define.h"
#include "mysql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <vector>
#include "../Protocol.h"
#include "../Define.h"
#include "../include/log_define.h"
#include "../netlib/HT_NET_Engine.h"
#include "../USERDEVDATA.h"
#include "../include/log_db.h"
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>

extern sem_t sem;
extern int sem_dbqueue_flag;
extern USERDEVDATA* user;

using namespace std;

MYSQL *db_mysql;


extern queue<DB_MSG*> db_queue;
extern queue<DB_MSG*>  hub_queue;
extern vector<int> realtime_log_fd;        //申请实时日志请求的连接套接字


void *db_thread_fun(void *arg)      //deal insert db
{
    printf("in db_thread_fun\n");
    while(1){
        while(db_queue.size() != 0){
            DB_MSG *dbmsg = db_queue.front();
            sem_dbqueue_flag = 0;
            Deal_db_Switch((void*)dbmsg);
            delete [] (char*)(dbmsg->msg);
            delete dbmsg;
            db_queue.pop();
        }
        sem_dbqueue_flag = 1;
        sem_wait(&sem);
    }

    return NULL;
}

int Deal_db_Switch(void*msg)
{
    printf("in Deal_db_Switch\n");
    DB_MSG *dbmsg = (DB_MSG*)msg;
    HEAD* head = (HEAD*)(dbmsg->msg);
    printf("head->PackType is %x\n",head->PackType);
    switch(head->PackType){
        case NET_PACKTYPE_LOG_WRITE:{        //wirite log
            insert_db(msg);
            break;
        }
        case NET_PACKTYPE_LOG_REQUSE_QUERY:{    //query log
            printf("查询日志\n");
            query_db(msg);
            break;
        }
        case NET_PACKTYPE_LOG_DOWNLOAD:{    //download log
            break;
        }
        case NET_PACKTYPE_LOG_GETLOGTYPEOBJ:{
            GetLogTypeObj(msg);
            break;
        }
        case NET_PACKTYPE_LOG_GETLOGTYPE:{
            GetLogType(msg);
            break;
        }
        case NET_PACKTYPE_LOG_SREACH_REALTIMELOG:{
            RealTimeLogRequest(msg);
            break;
        }
        case NET_PACKTYPE_LOG_ADDSOURCETYPE:{
            AddSourceType(msg);
            break;
        }
        case NET_PACKTYPE_LOG_ADDLOGTYPE:{
            AddLogType(msg);
            break;
        }
        case NET_PACKTYPE_LOG_DELSOURCETYPE:{
            DelSourceType(msg);
            break;
        }
        case NET_PACKTYPE_LOG_DELLOGTYPE:{
            DelLogType(msg);
            break;
        }
        default:
            break;
    }

}

int insert_db(void*msg)        //
{
    printf("in insert_db\n");
    DB_MSG *dbmsg = (DB_MSG*)msg;
    HEAD* head = (HEAD*)(dbmsg->msg);
    HT_LOG*  log= (HT_LOG*)(((char*)(dbmsg->msg))+sizeof(HEAD));

    if(log->object == 1){
        USERINFO*  m_usr = user->usr_map[log->objectID];
        if(m_usr == NULL){
            printf("insert log error  because there have not some one objectID is %d\n",log->objectID);
            return 1;
        }
        printf("insert user name is %s\n",m_usr->Name);
        memcpy(log->name,m_usr->Name,strlen(m_usr->Name));
    }
    else{
        DEVICE* dev = user->dev_map[log->objectID];
        if(dev != NULL)
            memcpy(log->name,dev->name,strlen(dev->name));
        else
            printf("can not find the dev obj\n");
    }

    printf("log->time %d\n",log->time);
    printf("log->type %d\n",log->type);

    char sqlstr[512] = {0};
    sprintf(sqlstr,"INSERT INTO logdatabase(m_time,m_type,context,m_obj,m_objID,m_name)VALUE(%d,%d,'%s',%d,%d,'%s');",\
            log->time, log->type, log->content,log->object,log->objectID,log->name);
            printf("%s\n",sqlstr);
        mysql_query(db_mysql, sqlstr);
    return 1;
}

string query_limit(char* query)
{
    HT_READ_QUERY* req = (HT_READ_QUERY* )query;
    stringstream stream;
    string terminal;
    terminal = "select * from logdatabase where";
    if(req->queryFlag != 1){
        printf("req->starttime is %d\n",req->starttime);
        if(req->starttime!=0){
            string s_time;
            stringstream time;
            time<<(req->starttime);
            time>>s_time;
            time.clear();
            string e_time;
            time<<(req->endtime);
            time>>e_time;
            if((req->object!=0) | (req->type)!=0)
                terminal = terminal+" m_time between "+s_time+" and "+e_time+" and";
            else
                terminal = terminal+" m_time between "+s_time+" and "+e_time;
            printf("in here?\n");
        }

        if(req->object!=0){
            string obj;
            stringstream s_obj;
            s_obj<<req->object;
            s_obj>>obj;
            if(req->type!=0)
                terminal = terminal+" m_obj="+obj+" and";
            else
                terminal = terminal+" m_obj="+obj;

        }

        if(req->type!=0){
            string type;
            stringstream s_type;
            s_type<<req->type;
            s_type>>type;
            cout<<"type is "<<type<<endl;
            int t_type = strtol(type.data(),NULL,0);
            cout<<"t_type is "<<t_type<<endl;
            type.clear();
            s_type.clear();
            s_type<<t_type;
            s_type>>type;
            terminal = terminal+" m_type="+type;
        }
        if((req->starttime==0)&&(req->object==0)&&(req->type==0)){
            terminal.clear();
            terminal = "select * from logdatabase";
        }

    }
    return terminal = terminal+";";
}

int query_db(void*msg)
{

    MYSQL_RES * res ;//保存查询结果
    MYSQL_ROW row ;
    int num_row = 0;//得到记录数量
    int alldata_num=0;
    char sqlstr[512] = {0};
    DB_MSG *dbmsg = (DB_MSG*)msg;
    HEAD* head = (HEAD*)(dbmsg->msg);
    HT_READ_QUERY* req = (HT_READ_QUERY*)(((char*)(dbmsg->msg))+sizeof(HEAD));

    string terminal = query_limit((char*)req);
    cout<<terminal<<endl;
    HT_LOG_ITEM* ite = NULL;
    int row_count;
    mysql_query(db_mysql, terminal.data());
    res = mysql_store_result(db_mysql);
    row_count = mysql_num_rows(res);
    row = mysql_fetch_row(res);
    ite=  new HT_LOG_ITEM[row_count];
    memset(ite,0,sizeof(HT_LOG_ITEM)*row_count);
    for(int i = 0;i<row_count;i++){
        ite[i].list_num = atoi(row[0]);
        ite[i].time = atoi(row[1]);
 //       printf("**********************\n");

       // char str[16] = {0};
      //  sprintf(str,"%x",atoi(row[2]));
        LogType * t_type = NULL;
        map<int,LogType*>::iterator item;
        item = user->LogType_map.find(atoi(row[2]));
        if(item!= user->LogType_map.end()){
            t_type = item->second;
            memcpy(ite[i].type,t_type->name,64);
        }

        LogObjType* t_objType = NULL;
        if(LOG_OBJECT_USER == atoi(row[4])){     // it is user obj
            t_objType = user->LogTypeObj_map[atoi(row[4])];
            memcpy(ite[i].objtype,t_objType->name,32);
            USERINFO*  m_usr = user->usr_map[atoi(row[5])];
       //     printf("**********************\n");
            memcpy(ite[i].obj,row[6],64);
        }
        else{
            t_objType = user->LogTypeObj_map[atoi(row[4])];
            memcpy(ite[i].objtype,t_objType->name,32);
            memcpy(ite[i].obj,row[6],64);
        }

        if(NULL != row[3]){
            memcpy(ite[i].context,row[3],strlen(row[3]));
           // printf("%s\n",row[3]);
        }
        row = mysql_fetch_row(res);
    }

    HT_RETURN_LOG hd_log;
    hd_log.datanum = row_count;
    hd_log.totalnum = row_count;
    hd_log.queryid = 1;
    hd_log.logSearch = req->logSearch;

    HEAD t_head;
    t_head.SysMark = NET_SYSTEM_MASK_HTP;
    t_head.ModuleMark = NET_MOUDLE_MASK_LOG;
    t_head.PackType = NET_PACKTYPE_LOG_RESPONSE_QUERY;
    t_head.PackSize = sizeof(HEAD)+sizeof(HT_RETURN_LOG)+sizeof(HT_LOG_ITEM)*row_count;
    t_head.DataSize = t_head.PackSize-sizeof(HEAD);
    char* buff = new char[t_head.PackSize];
    memset(buff,0,t_head.PackSize);
    memcpy(buff,&t_head,sizeof(HEAD));
    memcpy(buff+sizeof(HEAD),&hd_log,sizeof(hd_log));
    memcpy(buff+sizeof(HEAD)+sizeof(hd_log),ite,sizeof(HT_LOG_ITEM)*row_count);
    Tcp_SendMsg((conn_t*)dbmsg->sid,buff,t_head.PackSize);
    return 1;
}

int init_db(void)
{
    db_mysql = mysql_init(NULL);
    char* localIP = GetLocalIP();
    if(db_mysql == NULL)
        printf("little memory\n");
    printf("open mysql log databases\n");
    mysql_real_connect(db_mysql,localIP,"root","haotel","sys_log",0,NULL,0);
    delete [] localIP;
    printf("open log databases successful\n");
    mysql_set_character_set(db_mysql,"UTF8");
    return 1;
}

int db_exit(void)
{
  //  pthread_join(db_threadid, NULL);
    return 1;
}


void GetLogTypeObj(void* msg)
{
    HEAD t_head;
    DB_MSG *dbmsg = (DB_MSG*)msg;
    printf("Get GetLogTypeGrp\n");
    map<int,LogObjType*>::iterator ite;
    int num = user->LogTypeObj_map.size();
    char* buff = new char[sizeof(LogObjType)* num];
    memset(buff,0,sizeof(LogObjType)*num);
    int i = 0;
    for(ite = user->LogTypeObj_map.begin();ite!=user->LogTypeObj_map.end();ite++){
        memcpy(buff+i*sizeof(LogObjType),ite->second,sizeof(LogObjType));
        i++;
    }

     SendDataToSys((conn_t*)dbmsg->sid,NET_PACKTYPE_LOG_GETLOGTYPEOBJ,0,buff,sizeof(LogObjType)* num);
     delete [] buff;

}
void GetLogType(void* msg)
{
    DB_MSG *dbmsg = (DB_MSG*)msg;
    printf("Get GetLogType\n");
    map<int,LogType*>::iterator ite;
    int num = user->LogType_map.size();
    printf("<FILE %s;  LINE %d>log type count is %d\n",__FILE__,__LINE__,num);
    char* buff = new char[sizeof(LogType)* num];
    memset(buff,0,sizeof(LogType)*num);

    int i = 0;
    for(ite = user->LogType_map.begin();ite!=user->LogType_map.end();ite++){
        memcpy(buff+i*sizeof(LogType),ite->second,sizeof(LogType));
        i++;
    }

     SendDataToSys((conn_t*)dbmsg->sid,NET_PACKTYPE_LOG_GETLOGTYPE,0,buff,sizeof(LogType)* num);
     delete [] buff;
}

void RealTimeLogRequest(void* msg)
{
    printf("run to RealTimeLogRequest\n");
    DB_MSG *dbmsg = (DB_MSG*)msg;
    vector<int>::iterator v_ite;
    for(v_ite = realtime_log_fd.begin();v_ite!=realtime_log_fd.end();v_ite++){
        if(*v_ite == dbmsg->sid){
            printf("it is have in list\n");
            return;
        }
    }
    realtime_log_fd.push_back(dbmsg->sid);
}

void AddSourceType(void* msg)
{

    string terminal("select max(m_obj) from logobj;");
    mysql_query(db_mysql, terminal.data());
    MYSQL_RES *res = mysql_store_result(db_mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    int max = atoi(row[0]);
    mysql_free_result(res);

    terminal = "select max(ID) from logobj;";
    mysql_query(db_mysql, terminal.data());
    res = mysql_store_result(db_mysql);
    row = mysql_fetch_row(res);
    int maxID = atoi(row[0]);
    mysql_free_result(res);

    DB_MSG *dbmsg = (DB_MSG*)msg;
    int cnt = ((dbmsg->datalen)-sizeof(HEAD))/sizeof(LogObjType);
    char* buff = new char[sizeof(LogObjType)*cnt];
    memset(buff,0,sizeof(LogObjType)*cnt);
    for(int i = 0;i<cnt;i++){
        LogObjType* source = new LogObjType;
        memset(source,0,sizeof(LogObjType));
        memcpy(source,((char*)(dbmsg->msg)+sizeof(HEAD)+i*sizeof(LogObjType)),sizeof(LogObjType));
        source->ID = maxID+i+1;
        source->type = max+i+1;
        stringstream sql;
        sql<<"insert into logobj(ID,m_obj,m_objname)values("<<source->ID<<","<<source->type<<",'"<<source->name<<"');";
        terminal = sql.str();
        mysql_query(db_mysql, terminal.data());
        user->LogTypeObj_map[source->type] = source;
        memcpy(buff+i*sizeof(LogObjType),source,sizeof(LogObjType));
    }

    SendDataToSys((conn_t*)dbmsg->sid,NET_PACKTYPE_LOG_ADDSOURCETYPE,0,buff,sizeof(LogObjType)* cnt);

}

void AddLogType(void* msg)
{
    DB_MSG *dbmsg = (DB_MSG*)msg;
    int cnt = ((dbmsg->datalen)-sizeof(HEAD))/sizeof(LogType);

    char* buff = new char[sizeof(LogType)*cnt];
    memset(buff,0,sizeof(LogType)*cnt);

    LogType* first = (LogType*)((char*)(dbmsg->msg)+sizeof(HEAD));
    string terminal;

        stringstream sql;
        int min = (first->type_obj)*10000;
        int max = (first->type_obj+1)*10000;

        sql<<"select max(ID) from logtype where ID>"<<min<<" and ID<"<<max<<";";
        terminal = sql.str();
        mysql_query(db_mysql, terminal.data());
        sql.clear();
        terminal.clear();

        mysql_query(db_mysql, terminal.data());
        MYSQL_RES *res = mysql_store_result(db_mysql);
        MYSQL_ROW row = mysql_fetch_row(res);
        int ID;
        if(NULL == row[0])
            ID = min;
        else
            ID = atoi(row[0]);
        mysql_free_result(res);

    for(int i = 0;i<cnt;i++){
        LogType* type = new LogType;
        memset(type,0,sizeof(LogType));
        memcpy(type,((char*)(dbmsg->msg)+sizeof(HEAD)+i*sizeof(LogType)),sizeof(LogType));

        stringstream insert_sql;
        type->ID = ID+1;
        ID++;
        insert_sql<<"insert into logtype(ID,type_name,obj_type)values("<<type->ID<<",'"<<type->name<<"',"<<type->type_obj<<");";
        terminal = insert_sql.str();
        printf("add type insert_sql is \n%s\n",terminal.data());

        mysql_query(db_mysql, terminal.data());
        mysql_commit(db_mysql);
        insert_sql.clear();
        terminal.clear();
        user->LogType_map[type->ID] = type;
        memcpy(buff+i*sizeof(LogType),type,sizeof(LogType));
    }

    SendDataToSys((conn_t*)dbmsg->sid,NET_PACKTYPE_LOG_ADDLOGTYPE,0,buff,sizeof(LogType)* cnt);



}


void DelSourceType(void* msg)
{
    DB_MSG *dbmsg = (DB_MSG*)msg;
    LogObjType* source = (LogObjType*)((char*)(dbmsg->msg)+sizeof(HEAD));
    string terminal;
    stringstream sql;
    sql<<"delete from logobj where ID="<<source->ID<<";";
    terminal = sql.str();
    printf("del source sql is \n%s\n",terminal.data());
    mysql_query(db_mysql, terminal.data());

    map<int,LogObjType*>::iterator item;
    item = user->LogTypeObj_map.find(source->type);
    if(item!=user->LogTypeObj_map.end()){
        user->LogTypeObj_map.erase(item);

        map<int,LogType*>::iterator t_item;
        for(t_item = user->LogType_map.begin();t_item!=user->LogType_map.end();){
            LogType* type = t_item->second;
            if(type->type_obj == source->type){
                map<int,LogType*>::iterator tt_item;
                tt_item = t_item;

                user->LogType_map.erase(t_item++);

                string typeterminal;
                stringstream typesql;
                printf("del type ID is %d\n",type->ID);
                typesql<<"delete from logtype where ID="<<type->ID<<";";
                typeterminal = typesql.str();
                printf("del type sql is \n%s\n",typeterminal.data());
                mysql_query(db_mysql, typeterminal.data());
            }
            else
                t_item++;
        }
    }


}
void DelLogType(void* msg)
{
    DB_MSG *dbmsg = (DB_MSG*)msg;
    LogType* type = (LogType*)((char*)(dbmsg->msg)+sizeof(HEAD));
    string terminal;
    stringstream sql;
    sql<<"delete from logtype where ID="<<type->ID<<";";
    terminal = sql.str();
    printf("del type sql is \n%s\n",terminal.data());
    mysql_query(db_mysql, terminal.data());

    map<int,LogType*>::iterator item;
    item = user->LogType_map.find(type->ID);
    if(item != user->LogType_map.end()){
        delete item->second;
        user->LogType_map.erase(item);
    }

}

char* GetLocalIP()
{
     int sock;
     struct sockaddr_in sin;
     struct ifreq ifr;

     sock = socket(AF_INET, SOCK_DGRAM, 0);
     if (sock == -1)
     {
          perror("socket");
          return NULL;
     }

     strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);
     ifr.ifr_name[IFNAMSIZ - 1] = 0;

     if (ioctl(sock, SIOCGIFADDR, &ifr) < 0)
     {
          perror("ioctl");
          return NULL;
     }

     memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
     char* ip = new char[32];
     memset(ip,0,32);
     //fprintf(stdout, "eth0: %s\n", inet_ntoa(sin.sin_addr));
     memcpy(ip,inet_ntoa(sin.sin_addr),32);
     printf("local ip is %s\n",ip);
     return ip;
}


void SendDataToSys(conn_t* fd,int mark,int result,char* data,int len)
{
     HEAD t_head;
    t_head.SysMark = NET_SYSTEM_MASK_HTP;
    t_head.ModuleMark = NET_MOUDLE_MASK_LOG;
    t_head.PackType = mark;
    t_head.PackSize = sizeof(HEAD)+len;
    t_head.DataSize = len;
    char* buff = new char[sizeof(HEAD)+len];
    memset(buff,0,sizeof(HEAD)+len);
    memcpy(buff,&t_head,sizeof(HEAD));
    if(data != NULL)
        memcpy(buff+sizeof(HEAD),data,len);
    Tcp_SendMsg(fd,buff,t_head.PackSize);
    delete [] buff;
}
