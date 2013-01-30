

#include "mysql/mysql.h"
#include "../../include/init/Mem_Data.h"
#include "../../include/define/Define.h"
#include <iostream>
extern MYSQL mysql;


MEM_DATA::MEM_DATA()
{
        Device_Block = NULL;
        User_Block = NULL;
        Usergroup_Block = NULL;

}

MEM_DATA::~MEM_DATA()
{
        delete [] Device_Block;
        delete [] User_Block;
        delete [] Usergroup_Block;
}

char* MEM_DATA::Get_Device_Block()
{
    num = new COUNT;
    memset(num,0,sizeof(COUNT));
    mysql_query(&mysql,"select * from dev;");
    MYSQL_RES *p = mysql_store_result(&mysql);
    int rowcount = mysql_num_rows(p);
    num->Count_Device = rowcount;
    printf("count device is %d\n",num->Count_Device);
    MYSQL_ROW row = mysql_fetch_row(p);

    for(int i = 0;i<rowcount;i++){
        NODE* node_dev = new NODE;
        memset(node_dev,0,sizeof(NODE));
        node_dev->device.ID = atoi(row[0]);
     //   printf("(node_dev+i)->device.ID is >>>> %d \n",(node_dev+i)->device.ID);
        node_dev->device.group_ID = atoi(row[1]);
   //     printf("(node_dev+i)->device.group_ID is >>>> %d \n",(node_dev+i)->device.group_ID);
        memcpy(node_dev->device.name,row[2],64);
    //    printf("(node_dev+i)->device.name is >>>> %s \n",(node_dev+i)->device.name);
        node_dev->device.type = atoi(row[3]);
  //      printf("(node_dev+i)->device.type is >>>> %d \n",(node_dev+i)->device.type);
        memcpy(node_dev->device.model,row[4],32);
   //     printf("(node_dev+i)->device.model is >>>> %s \n",(node_dev+i)->device.model);
        memcpy(node_dev->device.sys_num,row[5],32);
        node_dev->device.status = DEVICE_STATUS_OFFLINE;

        memcpy(node_dev->device.IP ,row[6],strlen(row[6]));
        node_dev->device.port = atoi(row[7]);
        Device_map[node_dev->device.ID] = node_dev;
        row = mysql_fetch_row(p);
    }
    mysql_free_result(p);
    printf("get dev blocks OK\n");
    Get_DeviceGroup_Block();
    Get_LimitBlock();
    Get_Device_Channel();
    Get_Monitor_Block();

}

char* MEM_DATA::Get_Device_Channel()
{



    mysql_query(&mysql,"select * from channel;");
    MYSQL_RES *p = mysql_store_result(&mysql);
    int rowcount = mysql_num_rows(p);
    MYSQL_ROW row = mysql_fetch_row(p);
    num->Count_Channel = rowcount;
    for(int i = 0;i<rowcount;i++){
        DEVICE_CHANNEL*  node_channel = new DEVICE_CHANNEL;
        memset(node_channel,0,sizeof(DEVICE_CHANNEL));
        node_channel->ID = atoi(row[0]);
        memcpy(node_channel->name,row[1],strlen(row[1]));
        node_channel->group_ID = atoi(row[2]);
        node_channel->chn_num = atoi(row[3]);
        DeviceChnnel_map[ node_channel->ID] = node_channel;
        row = mysql_fetch_row(p);
    }
    mysql_free_result(p);
}

char* MEM_DATA::Get_LimitBlock()
{
    mysql_query(&mysql,"select * from usr_limit;");
    MYSQL_RES *p = mysql_store_result(&mysql);
    int rowcount = mysql_num_rows(p);
    MYSQL_ROW row = mysql_fetch_row(p);

    num->Count_Power = rowcount;

    for(int i = 0;i<rowcount;i++){
        LIMIT*  limit = new LIMIT;
        memset(limit,0,sizeof(LIMIT));
        limit->ID = atoi(row[0]);
        limit->PID = atoi(row[1]);
        limit->type = atoi(row[2]);
        limit->able = atoi(row[4]);
        memcpy(limit->name,row[3],strlen(row[3]));
        Power_map[limit->ID ] = limit;
        row = mysql_fetch_row(p);
    }
    mysql_free_result(p);
    printf("get power blocks OK\n");
}

char* MEM_DATA::Get_DeviceGroup_Block()
{
    mysql_query(&mysql,"select * from dev_group;");
    MYSQL_RES *p = mysql_store_result(&mysql);
    int rowcount = mysql_num_rows(p);
    num->Count_Group = rowcount;
    MYSQL_ROW row = mysql_fetch_row(p);

    for(int i = 0;i<rowcount;i++){
        NODE_GRP* node_devGroup = new NODE_GRP;
        memset(node_devGroup,0,sizeof(NODE_GRP));
        node_devGroup->device_grp.ID = atoi(row[0]);
        node_devGroup->device_grp.PID = atoi(row[2]);
        memcpy(node_devGroup->device_grp.name,row[1],64);
        node_devGroup->device_grp.lev = atoi(row[3]);
        DeviceGrp_map[node_devGroup->device_grp.ID] = node_devGroup;
        row = mysql_fetch_row(p);
    }
    mysql_free_result(p);
    printf("get dev group blocks OK\n");

}


char* MEM_DATA::Get_User_Block()
{
    mysql_query(&mysql,"select * from user_new;");
    MYSQL_RES* p = mysql_store_result(&mysql);
    int row_user = mysql_num_rows(p);
    MYSQL_ROW row = mysql_fetch_row(p);
    user_count = new USERCOUNT;
    memset(user_count,0,sizeof(USERCOUNT));
    user_count->Count_User = row_user;
    printf("user count is %d\n",row_user);
    for( int i  = 0;i<row_user;i++){
        USERINFO *user = new USERINFO;
        memset(user,0,sizeof(USERINFO));
        memcpy(user->Name,row[1],strlen(row[1]));
        printf("user name is %s\n",user->Name);
        memcpy(user->PassWord,row[2],strlen(row[2]));
        user->ID = atoi(row[0]);
        if(row[5] != NULL){
            memcpy(user->power_ID,row[5],strlen(row[5]));
        }
        if(row[6] != NULL){
            memcpy(user->power_dev,row[6],strlen(row[6]));
        }
        string str(user->Name);
        User_map[str] = user;
        row = mysql_fetch_row(p);
    }
    mysql_free_result(p);
    printf("get user blocks OK\n");
}

char* MEM_DATA::Get_Monitor_Block()
{
    mysql_query(&mysql,"select * from monitor_center;");

    MYSQL_RES* p = mysql_store_result(&mysql);
    int row_user = mysql_num_rows(p);
    MYSQL_ROW row = mysql_fetch_row(p);
    num->Count_Stream = row_user;
    for( int i  = 0;i<row_user;i++){
        MONITOR_CENTER *monitor = new MONITOR_CENTER;
        memset(monitor,0,sizeof(MONITOR_CENTER));
        monitor->ID = atoi(row[0]);
        memcpy((monitor)->name,row[1],strlen(row[1]));
        monitor->type = atoi(row[2]);
        monitor->PID = atoi(row[3]);
        monitor->lev = atoi(row[4]);
        memcpy(monitor->IP,row[5],strlen(row[5]));
        monitor->port = atoi(row[6]);
        monitor_map[monitor->ID] = monitor;
        row = mysql_fetch_row(p);
    }
    mysql_free_result(p);
    printf("get monitor blocks OK\n");
}

int MEM_DATA::Search_User_PowerID(char* name)
{


}

SendData* MEM_DATA::User_Device(int power_ID)
{


}

