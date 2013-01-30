#include "../../include/userJob/UserloginJob.h"
#include "../../HT_Platform_ResultCode.h"
#include "../../include/define/Define_Page.h"
#include "../../include/log/log_data.h"
#include "../../include/log/write_log.h"
#include <iostream>
#include <sstream>

//Test
#include <string>

extern ObjectFactoy *m_fator;
extern MYSQL mysql;



//其它模块各项操作函数入口
void UserloginJob::MCS(unsigned long packType)
{
    printf("packType is    ___________  %x\n",packType);
    switch (packType){

            case NET_PACKTYPE_MCS_REQUSET_REGMOUDLE:     //模块注册
            {
                ServerLogin();
                break;
            }
            case NET_PACKTYPE_MCS_UNREGMOUDLE:           //取消模块注册
            {
                break;
            }
            case NET_PACKTYPE_MCS_REQUEST_DEVICETREE:       //请求设备树
            {
                Request_Device();
                break;
            }
            case NET_PACKTYPE_MCS_RESPONSEUSERS:
            {
                AllUser();
                break;
            }
            case NET_PACKTYPE_MCS_QUEST_POWER_TREE:
            {
                Requset_PowerTree();
                break;
            }
            case NET_PACKTYPE_MCS_REQUSET_QUERYSESSION:     //查询会话
            {
                break;
            }
            case NET_PACKTYPE_MCS_REQUSET_QUERYPOWER:       //查询权限
            {
                printf("权限查询\n");
                Query_Power();
                break;
            }
            case NET_PACKTYPE_MCS_QUEST_MSSINFO:
            {
                memcpy(&(m_fator->mssinfo),((MSSINFO*)((qdata->Buf)+sizeof(HEAD))),sizeof(MSSINFO));
                break;
            }
            case NET_PACKTYPE_MCS_ADDDEVICE:        //添加设备
            {
                Add_Device();
                break;
            }
            case NET_PACKTYPE_MCS_EDITDEVICE:       //修改设备
            {
                Change_Device();
                break;
            }
            case NET_PACKTYPE_MCS_DELETEDEVICE:     //删除设备
            {
                Del_Device();
                break;
            }
            case NET_PACKTYPE_MCS_ADDUSER:
            {
                AddUser();
                break;
            }
            case NET_PACKTYPE_MCS_EDITUSER:
            {
                ModifyUser();
                break;
            }
            case NET_PACKTYPE_MCS_DELETEUSER:
            {
                DelUser();
                break;
            }

            case NET_PACKTYPE_MCS_ADDDEVGRP:        //增加设备分组
            {
                Add_DeviceGroup();
                break;
            }
            case NET_PACKTYPE_MCS_MODIFYGRP:
            {
                printf("modify device group\n");
                Change_DeviceGroup();
                break;
            }
            case NET_PACKTYPE_MCS_DELDEVGRP:        //删除设备分组
            {
                printf("删除设备分组\n");
                Del_DeviceGrp();
                break;
            }
            case NET_PACKTYPE_MCS_QUEST_DEVICESTATUS:
            {
                Request_DeviceStatus();
                break;
            }

            case NET_PACKTYPE_MCS_GETDEVINFO:
            {
                printf("获取设备信息\n");
                break;
            }
            case NET_PACKTYPE_MCS_REQUEST_STREAM_TREE:
            {
                printf("quest stream tree data\n");
                Request_StreamTree();
                break;
            }
            default:
                printf("application error\n");
    }
}

void UserloginJob::ServerLogin()
{
    HEAD * head = (HEAD*)(qdata->Buf);
    char* s_info = (qdata->Buf)+sizeof(HEAD);
    ServerInfo* t_info = (ServerInfo*)s_info;
    printf("login servers ip is %s  port is %d\n",t_info->m_Addr,t_info->m_Port);

    switch(head->ModuleMark){
        case NET_MOUDLE_MASK_ALM:m_fator->SetAlarmSocket(qdata->fd);m_fator->SetAlarmServerInfo(s_info);printf("alarm login\n");break;
        case NET_MOUDLE_MASK_MSS:m_fator->SetStreamSocket(qdata->fd);m_fator->SetStreamServerInfo(s_info);printf("stream login\n");break;
        case NET_MOUDLE_MASK_LOG:m_fator->SetLogServerInfo(s_info);printf("log login\n");break;
        case NET_MOUDLE_MASK_MTX:m_fator->SetTVWallSocket(qdata->fd);m_fator->SetTVWallServerInfo(s_info);printf("tv wall login\n");break;
        case NET_MOUDLE_MASK_STG:m_fator->SetStorageSocket(qdata->fd);m_fator->SetStorageServerInfo(s_info);printf("storage login\n");break;
        default:
            break;
    }
    Request_Data(NET_PACKTYPE_MCS_RESPONSE_REGMOUDLE,NULL,HT_PLATFORM_RESULTCODE_SUCESS,0,0);
}

//设备组
void UserloginJob::Add_DeviceGroup()
{
    NODE_GRP* dev_grp_node = new NODE_GRP;
    memset(dev_grp_node,0,sizeof(NODE_GRP));
    memcpy(&(dev_grp_node->device_grp),(DEVICE_GRP*)((qdata->Buf)+sizeof(HEAD)),sizeof(DEVICE_GRP));
    printf("new dev_grp name is %s\n",dev_grp_node->device_grp.name);
    printf("new dev_grp PID is %d\n",dev_grp_node->device_grp.PID);
    printf("new dev_grp lev is %d\n",dev_grp_node->device_grp.lev);

    char terminal[512] = {0};
    sprintf(terminal,"select max(ID) as ID from dev_group;");
    mysql_query(&mysql,terminal);
    MYSQL_RES *p = mysql_store_result(&mysql);
    MYSQL_ROW row = mysql_fetch_row(p);
    if(NULL == row[0])
        dev_grp_node->device_grp.ID = 1;
    else
        dev_grp_node->device_grp.ID = atoi(row[0])+1;

    printf("新设备组节点ID 为%d\n",dev_grp_node->device_grp.ID);
    mysql_free_result(p);
    memset(terminal,0,512);
    sprintf(terminal,"insert into dev_group (ID,g_name,PID,lev)values(%d,'%s',%d,%d);",dev_grp_node->device_grp.ID,dev_grp_node->device_grp.name,dev_grp_node->device_grp.PID,dev_grp_node->device_grp.lev);
    mysql_query(&mysql,terminal);

    //将新节点加入到设备组map表中
    m_fator->m_MemData.DeviceGrp_map[dev_grp_node->device_grp.ID] = dev_grp_node;
    COUNT* count_tmp = m_fator->m_MemData.Get_AllDev_Count();
    count_tmp->Count_Group++;
    Request_Data(NET_PACKTYPE_MCS_ADDDEVGRP,(char*)&(dev_grp_node->device_grp),HT_PLATFORM_RESULTCODE_SUCESS,0,sizeof(DEVICE_GRP));

}

void UserloginJob::Change_DeviceGroup()
{

    DEVICE_GRP* t_grp = (DEVICE_GRP*)((qdata->Buf)+sizeof(HEAD));
    printf("grp name is %s\n",t_grp->name);
    char terminal[512] = {0};
    sprintf(terminal,"update dev_group set g_name='%s' where ID=%d;",t_grp->name,t_grp->ID);
    printf("%s\n",terminal);
     mysql_query(&mysql,terminal);

}

//DEVICE
void UserloginJob::Add_Device()
{
    printf("增加设备\n");
    NODE* device_node = new NODE;
    memcpy(&(device_node->device),(qdata->Buf)+sizeof(HEAD),sizeof(DEVICE));
    int channel_count = 0;
    switch(device_node->device.type ){
        case DEVICE_TYPE_HK:channel_count = 4;break;
        case DEVICE_TYPE_GH:channel_count = 0;break;
        case DEVICE_TYPE_HB:channel_count = 16;break;
        case DEVICE_TYPE_DH:channel_count = 0;break;
        case DEVICE_TYPE_JG:channel_count = 0;break;
        case DEVICE_TYPE_WD:channel_count = 0;break;
        case DEVICE_TYPE_DJL:channel_count = 0;break;
        case DEVICE_TYPE_WL:channel_count = 0;break;
        case DEVICE_TYPE_SMOKE:channel_count = 1;break;
        case DEVICE_TYPE_LED:channel_count = 1;break;
        case DEVICE_TYPE_LIGHT:channel_count = 1;break;
        default:break;
    }
    DEVBELONGUSER* belong = (DEVBELONGUSER*)((qdata->Buf)+sizeof(HEAD)+sizeof(DEVICE)+sizeof(DEVICE_CHANNEL)*channel_count);
    DEVICE_CHANNEL* chn = new DEVICE_CHANNEL[channel_count];
    memcpy(chn,(qdata->Buf)+sizeof(HEAD)+sizeof(DEVICE),channel_count*sizeof(DEVICE_CHANNEL));
    for(int i = 0;i<channel_count;i++)
        printf("chn name is  %s\n",(chn+i)->name);

  //  char terminal[512] = {0};
    stringstream stream;
    string terminal;
    stream<<"select max(ID) as ID from dev;";
    terminal = stream.str();
    cout<<terminal<<endl;
   // sprintf(terminal,"select max(ID) as ID from dev;");
    mysql_query(&mysql,terminal.data());
    stream.clear();
    terminal.clear();
    MYSQL_RES *p = mysql_store_result(&mysql);
    MYSQL_ROW row = mysql_fetch_row(p);
    int dev_new_ID;
    if(NULL == row[0])
        dev_new_ID = 10001;
    else
        dev_new_ID = atoi(row[0]) + 1;
    printf("max ID is %d\n",dev_new_ID);
    device_node->device.ID = dev_new_ID;

    stringstream stream_insert;
    stream_insert<<"insert into dev(ID,group_ID,dev_name,type,model,sys_num,dev_IP,dev_port)values("<<\
    device_node->device.ID<<","<<device_node->device.group_ID<<",'"<<device_node->device.name<<"',"<<\
    device_node->device.type<<",'"<<device_node->device.model<<"','"<<device_node->device.sys_num<<"','"<<\
    device_node->device.IP<<"',"<<device_node->device.port<<");";

    terminal = stream_insert.str();
    cout<< terminal<<endl;


   // sprintf(terminal,"insert into dev(ID,group_ID,dev_name,type,model,sys_num,dev_IP,dev_port)values(%d,%d,'%s',%d,'%s','%s','%s',%d);",\
     //       device_node->device.ID,device_node->device.group_ID,device_node->device.name,device_node->device.type,device_node->device.model,device_node->device.sys_num,device_node->device.IP,device_node->device.port);
    cout<<terminal<<endl;
    mysql_query(&mysql,terminal.data());

     stream_insert.clear();
    terminal.clear();

    int channelID = 0;
    stringstream stream_chnMax;
    stream_chnMax<<"select max(ID) as ID from channel;";

    terminal = stream_chnMax.str();

   // sprintf(terminal,"select max(ID) as ID from channel;");
   cout<<terminal<<endl;
    mysql_query(&mysql,terminal.data());
    stream_chnMax.clear();
    terminal.clear();
    p = mysql_store_result(&mysql);
    row = mysql_fetch_row(p);
    if(NULL == row[0])
        channelID = 100001;
    else
        channelID = atoi(row[0]) + 1;

    COUNT* count_tmp = m_fator->m_MemData.Get_AllDev_Count();

    for(int i = 0;i<channel_count;i++){
        (chn+i)->group_ID = device_node->device.ID;
        (chn+i)->ID = channelID+i;
        //sprintf(terminal,"insert into channel(ID,chn_name,chn_PID)values(%d,'%s',%d);",(chn+i)->ID,(chn+i)->name,(chn+i)->group_ID);
        stringstream stream_insert_chn;
        stream_insert_chn<<"insert into channel(ID,chn_name,chn_PID,chn_num)values("<<(chn+i)->ID<<",'"<<(chn+i)->name<<"',"<<(chn+i)->group_ID<<","<<(chn+i)->chn_num<<");";
        terminal = stream_insert_chn.str();
       cout<<terminal<<endl;
        mysql_query(&mysql,terminal.data());
        stream_insert_chn.clear();
        terminal.clear();
        m_fator->m_MemData.DeviceChnnel_map[(chn+i)->ID ] = chn+i;
        count_tmp->Count_Channel++;
    }
     m_fator->m_MemData.Device_map[device_node->device.ID] = device_node;
     count_tmp->Count_Device++;

     for(int i = 0;i<belong->num;i++){
            string str(belong->usr[i]);
            USERINFO* usr = m_fator->m_MemData.User_map[str] ;
            if(NULL != usr->power_dev )
                sprintf(usr->power_dev+strlen(usr->power_dev),",%d",device_node->device.ID);
            else
                sprintf(usr->power_dev+strlen(usr->power_dev),"%d",device_node->device.ID);

         //   sprintf(terminal,"update user_new set power_dev='%s' where ID=%d;",usr->power_dev,usr->ID);
            stringstream stream_update;
            stream_update<<"update user_new set power_dev='"<<usr->power_dev<<"' where ID="<<usr->ID;
            terminal = stream_update.str();
            cout<<terminal<<endl;
            mysql_query(&mysql,terminal.data());
            stream_update.clear();
            terminal.clear();
     }


     int len = channel_count*sizeof(DEVICE_CHANNEL)+sizeof(DEVICE)+sizeof(DEVBELONGUSER);
     char* buff = new char[len];
     memcpy(buff,&(device_node->device),sizeof(DEVICE));
     for(int i = 0;i<channel_count;i++){
        memcpy(buff+sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),chn+i,sizeof(DEVICE_CHANNEL));
     }
     memcpy(buff+sizeof(DEVICE)+channel_count*sizeof(DEVICE_CHANNEL),belong,sizeof(DEVBELONGUSER));
     Request_Data(NET_PACKTYPE_MCS_ADDDEVICE,buff,HT_PLATFORM_RESULTCODE_SUCESS,0,len);
     delete [] buff;
}


void UserloginJob::Change_Device()
{

    DEVICE* dev = (DEVICE*)((qdata->Buf)+sizeof(HEAD));
    NODE* device_node = m_fator->m_MemData.Device_map[dev->ID];
    if(NULL == device_node){
        printf("modify dev error\n");
        Request_Data(NET_PACKTYPE_MCS_EDITDEVICE,NULL,HT_PLATFORM_RESULTCODE_ERROR,0,0);
        return;
    }
    else{
        memset(&(device_node->device),0,sizeof(DEVICE));
        memcpy(&(device_node->device),dev,sizeof(DEVICE));
        char terminal[512] = {0};
        sprintf(terminal,"update dev set dev_name='%s',type=%d,model='%s',sys_num='%s',dev_IP='%s',dev_port=%d where ID=%d;",\
            device_node->device.name,device_node->device.type,device_node->device.model,device_node->device.sys_num,device_node->device.IP,\
            device_node->device.port,device_node->device.ID);

        if(0>mysql_query(&mysql,terminal))
            printf("update dev have someting wrong in mysql\n");
    }
    int channel_count = 0;
    switch(device_node->device.type ){
        case DEVICE_TYPE_HK: channel_count = 4;break;
        case DEVICE_TYPE_GH: channel_count = 0;break;
        case DEVICE_TYPE_HB: channel_count = 16;break;
        case DEVICE_TYPE_DH: channel_count = 0;break;
        case DEVICE_TYPE_JG: channel_count = 0;break;
        case DEVICE_TYPE_WD: channel_count = 0;break;
        case DEVICE_TYPE_DJL: channel_count = 0;break;
        case DEVICE_TYPE_WL: channel_count = 0;break;
        case DEVICE_TYPE_SMOKE: channel_count = 1;break;
        case DEVICE_TYPE_LED: channel_count = 1;break;
        case DEVICE_TYPE_LIGHT: channel_count = 1;break;
        default:break;
    }


    DEVBELONGUSER* belong = (DEVBELONGUSER*)((qdata->Buf)+sizeof(HEAD)+sizeof(DEVICE)+sizeof(DEVICE_CHANNEL)*channel_count);

    for(int i = 0;i<channel_count;i++){
        //memcpy(chn,(qdata->Buf)+sizeof(HEAD)+sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),sizeof(DEVICE_CHANNEL));
        DEVICE_CHANNEL* chn = (DEVICE_CHANNEL*)((qdata->Buf)+sizeof(HEAD)+sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL));

        DEVICE_CHANNEL* m_chn = m_fator->m_MemData.DeviceChnnel_map[chn->ID ];
        if(NULL == m_chn){
            printf("modify dev channel error\n");
        }
        else{
            memset(m_chn,0,sizeof(DEVICE_CHANNEL));
            memcpy(m_chn,chn,sizeof(DEVICE_CHANNEL));
            char terminal[512] = {0};
            sprintf(terminal,"update channel set chn_name='%s' where ID=%d;",m_chn->name,m_chn->ID);

            if(0>mysql_query(&mysql,terminal))
                printf("update dev channel have someting wrong in mysql\n");
        }

    }

    for(int i = 0;i<belong->cn_num;i++){
        string str(belong->cancel_usr[i]);
        USERINFO* usr = m_fator->m_MemData.User_map[str] ;
        if((usr== NULL)||(usr->power_dev == NULL)){
            printf("have something wrong with cancel user dev power\n");
            continue;
        }
        char tmp_dev[512] = {0};
        memcpy(tmp_dev,usr->power_dev,512);
        memset(usr->power_dev,0,512);

        char tmp_id[8] = {0};
        sprintf(tmp_id,"%d",dev->ID);
        printf("del power dev num is %s\n",tmp_dev);
        printf("tar str is %s\n",tmp_id);
        char* ret = strstr(tmp_dev,tmp_id);
        char* tok = NULL;
        char* sep = NULL;
        if(ret == NULL)
            continue;
        if(ret != tmp_dev) {//first id is the delete num
            *(ret-1) = 0;
        }

        tok = ret;
        printf("tok is %s\n",tok);
        sep = strsep(&tok,",");
        if(tok== NULL)
            sprintf(usr->power_dev,"%s",tmp_dev);
        else
            sprintf(usr->power_dev,"%s,%s",tmp_dev,tok);


        string s_terminal;
        stringstream stream_update;
        stream_update<<"update user_new set power_dev='"<<usr->power_dev<<"' where ID="<<usr->ID;
        s_terminal = stream_update.str();
        cout<<s_terminal<<endl;
        mysql_query(&mysql,s_terminal.data());
        stream_update.clear();
        s_terminal.clear();
        printf("new user power dev is %s\n",usr->power_dev);
        printf("belong->cancel_usr[%d] is %s\n",i,belong->cancel_usr[i]);
    }

    for(int i = 0;i<belong->num;i++){
        printf("dev belong user is  %s\n",belong->usr[i]);
        string str(belong->usr[i]);
        USERINFO* usr = m_fator->m_MemData.User_map[str] ;
        char tmp_id[8] = {0};
        sprintf(tmp_id,"%d",dev->ID);
        if(NULL == strstr(usr->power_dev,tmp_id)){
            if(0 != *(usr->power_dev) )
                    sprintf(usr->power_dev+strlen(usr->power_dev),",%d",device_node->device.ID);
            else
                    sprintf(usr->power_dev+strlen(usr->power_dev),"%d",device_node->device.ID);

        }

            string s_terminal;
            stringstream stream_update;
            stream_update<<"update user_new set power_dev='"<<usr->power_dev<<"' where ID="<<usr->ID;
            s_terminal = stream_update.str();
            cout<<s_terminal<<endl;
            mysql_query(&mysql,s_terminal.data());
            stream_update.clear();
            s_terminal.clear();
    }

     int len = channel_count*sizeof(DEVICE_CHANNEL)+sizeof(DEVICE)+sizeof(DEVBELONGUSER);
     char* buff = new char[len];
     memcpy(buff,&(device_node->device),sizeof(DEVICE));

     DEVICE_CHANNEL* chn = (DEVICE_CHANNEL*)((qdata->Buf)+sizeof(HEAD)+sizeof(DEVICE));
     for(int i = 0;i<channel_count;i++){
        memcpy(buff+sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),chn+i,sizeof(DEVICE_CHANNEL));
     }
     memcpy(buff+sizeof(DEVICE)+channel_count*sizeof(DEVICE_CHANNEL),belong,sizeof(DEVBELONGUSER));
     Request_Data(NET_PACKTYPE_MCS_EDITDEVICE,buff,HT_PLATFORM_RESULTCODE_SUCESS,0,len);
     delete [] buff;


}

//删除设备
void UserloginJob::Del_Device()
{
    printf("******************\n");
    printf("删除设备\n");
    DEVICE device;
    char terminal[512];
    memcpy(&device,(qdata->Buf)+sizeof(HEAD),sizeof(DEVICE));
    printf("ID is %d\n",device.ID);
    sprintf(terminal,"delete from dev where ID=%d;",device.ID);     //删除行
    mysql_query(&mysql,terminal);
    memset(terminal,0,512);
    sprintf(terminal,"delete from channel where chn_PID=%d;",device.ID);     //删除行
    COUNT* node_count = m_fator->m_MemData.Get_AllDev_Count();
    node_count->Count_Device--;

    NODE* t_node = m_fator->m_MemData.Device_map[device.ID];
    if(t_node == NULL){
        printf("no such device\n");
        return;
    }
    m_fator->m_MemData.Device_map.erase(device.ID);

    map<int,DEVICE_CHANNEL*>::iterator it_chn;
    map<int,DEVICE_CHANNEL*>::iterator t_it_chn;
    for(it_chn = m_fator->m_MemData.DeviceChnnel_map.begin();it_chn!=m_fator->m_MemData.DeviceChnnel_map.end();it_chn++){
        DEVICE_CHANNEL* t_chn = it_chn->second;
        if(t_chn->group_ID == device.ID){
            t_it_chn = it_chn;
            it_chn++;
            m_fator->m_MemData.DeviceChnnel_map.erase(t_it_chn);
            node_count->Count_Channel--;
        }
        else{
            ++it_chn;
        }
    }
}

void UserloginJob::AddUser()
{
    USERINFO* user_info = new USERINFO;
    memset(user_info,0,sizeof(USERINFO));
    char terminal[1024] = {0};

    sprintf(terminal,"select max(ID) as ID from user_new;");
    mysql_query(&mysql,terminal);
    MYSQL_RES *p = mysql_store_result(&mysql);
    MYSQL_ROW row = mysql_fetch_row(p);
    memcpy(user_info,(qdata->Buf)+sizeof(HEAD),sizeof(USERINFO));
    if(NULL == row[0])
        user_info->ID = 1;
    else
        user_info->ID = atoi(row[0]) + 1;
    printf("new user dev is %s\n",user_info->power_dev);
    memset(terminal,0,1024);
    sprintf(terminal,"insert into user_new (ID,user_name,user_pwd,user_PID,user_type,power_ID,power_dev)values(%d,'%s','%s',%d,%d,'%s','%s');",\
                                user_info->ID,user_info->Name,user_info->PassWord,user_info->PID,user_info->Type,user_info->power_ID,user_info->power_dev);
    printf("add new user is \n%s\n",terminal);
    mysql_query(&mysql,terminal);

    string str(user_info->Name);

    cout<<"str name is "<<str<<endl;
    m_fator->m_MemData.User_map[str] = user_info;

    USERCOUNT* usrCount = m_fator->m_MemData.Get_AllUser_Count();
    usrCount->Count_User++;


    Request_Data(NET_PACKTYPE_MCS_ADDUSER,(char*)user_info,HT_PLATFORM_RESULTCODE_SUCESS,1,sizeof(USERINFO));
}

void UserloginJob::ModifyUser()
{
    printf("modify userinfo\n");
    USERINFO user_info;
    memset(&user_info,0,sizeof(USERINFO));
    memcpy(&user_info,(qdata->Buf)+sizeof(HEAD),sizeof(USERINFO));
    string str(user_info.Name);
    USERINFO* usr = m_fator->m_MemData.User_map[str];
    if(usr== NULL){
        Request_Data(NET_PACKTYPE_MCS_EDITUSER,NULL,HT_PLATFORM_RESULTCODE_NOUSER,1,0);
        return;
    }

    stringstream sql;
    string terminal;
    sql<<"call modify_user('"<<user_info.PassWord<<"','"<<user_info.power_ID<<"','"<<user_info.power_dev<<"',"<<user_info.ID<<");";
    terminal = sql.str();
    mysql_query(&mysql,terminal.data());



    memset(usr->PassWord,0,16);
    memset(usr->power_ID,0,512);
    memset(usr->power_dev,0,512);
    memcpy(usr->PassWord,user_info.PassWord,strlen(user_info.PassWord));
    *((usr->PassWord)+strlen(user_info.PassWord)+1 ) = '\0';
    memcpy(usr->power_ID,user_info.power_ID,strlen(user_info.power_ID));
    *((usr->power_ID)+strlen(user_info.power_ID)+1 ) = '\0';
    memcpy(usr->power_dev,user_info.power_dev,strlen(user_info.power_dev));
    *((usr->power_dev)+strlen(user_info.power_dev)+1 ) = '\0';

    Request_Data(NET_PACKTYPE_MCS_EDITUSER,(char*)&user_info,HT_PLATFORM_RESULTCODE_SUCESS,1,sizeof(USERINFO));
}

void UserloginJob::DelUser()
{
    printf("Del user \n");
     USERINFO usr;
     memset(&usr,0,sizeof(USERINFO));
    char terminal[512];
    memcpy(&usr,(qdata->Buf)+sizeof(HEAD)+sizeof(MCSUSERLOGIN),sizeof(USERINFO));
    printf("del user ID is %d\n",usr.ID);
    sprintf(terminal,"delete from user_new where ID=%d;",usr.ID);     //删除行
    mysql_query(&mysql,terminal);
    string str(usr.Name);
    m_fator->m_MemData.User_map.erase(str);

    USERCOUNT* usrCount = m_fator->m_MemData.Get_AllUser_Count();
    usrCount->Count_User--;

}
