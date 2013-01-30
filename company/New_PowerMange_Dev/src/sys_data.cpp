#include "../include/data/sys_data.h"

SYSDATA::SYSDATA()
{
    dev_map.clear();
    devgroup_map.clear();
    user_map.clear();
    devchn_map.clear();
    monitor_map.clear();
    power_map.clear();
    powergrp_map.clear();
    poweritem_map.clear();
}
SYSDATA::~SYSDATA()
{

}
void SYSDATA::GetDeviceData(char* data)
{
    COUNT cout_node;
    memcpy(&cout_node,data,sizeof(COUNT));
//建立设备分组表
    for(int i = 0;i<cout_node.Count_Group;i++){
        DEVICE_GRP* grp = new DEVICE_GRP;
        memset(grp,0,sizeof(DEVICE_GRP));
        memcpy(grp,data+sizeof(COUNT)+i*sizeof(DEVICE_GRP),sizeof(DEVICE_GRP));
        devgroup_map[grp->ID] = grp;
        printf("devgroup_map.size() %d\n",devgroup_map.size());
    }
//建立设备节点表
    for(int i = 0;i<cout_node.Count_Device;i++){
        DEVICE* dev = new DEVICE;
        memset(dev,0,sizeof(DEVICE));
        memcpy(dev,data+sizeof(COUNT)+cout_node.Count_Group*sizeof(DEVICE_GRP)+i*sizeof(DEVICE),sizeof(DEVICE));
        dev_map[dev->ID] = dev;
        printf("dev_map.size() %d\n",dev_map.size());
    }

//建立设备通道表
    for(int i = 0;i<cout_node.Count_Channel;i++){
        DEVICE_CHANNEL* chn = new DEVICE_CHANNEL;
        memset(chn,0,sizeof(DEVICE_CHANNEL));
        memcpy(chn,data+sizeof(COUNT)+cout_node.Count_Group*sizeof(DEVICE_GRP)+cout_node.Count_Device*sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),sizeof(DEVICE_CHANNEL));
        devchn_map[chn->ID] = chn;
        printf("devchn_map.size() %d\n",devchn_map.size());

    }
    printf("build dev node map successful\n");

}

void SYSDATA::GetUserData(char* data)
{
    USERCOUNT cout_node;
    memcpy(&cout_node,data,sizeof(USERCOUNT));

    printf("user count is %d\n",cout_node.Count_User);

    for(int i = 0;i<cout_node.Count_User;i++){
        USERINFO* usr = new USERINFO;
        memset(usr,0,sizeof(USERINFO));
        memcpy(usr,data+sizeof(USERCOUNT)+i*sizeof(USERINFO),sizeof(USERINFO));
        user_map[usr->ID] = usr;
    }
    printf("build user node map successful\n");
}
void SYSDATA::GetMonitorData(char*data)
{
    COUNT cout_node;
    memcpy(&cout_node,data,sizeof(COUNT));
    for(int i = 0;i<cout_node.Count_Stream;i++){
        MONITOR_CENTER* monitor = new MONITOR_CENTER;
        memset(monitor,0,sizeof(MONITOR_CENTER));
        memcpy(monitor,data+sizeof(COUNT)+i*sizeof(MONITOR_CENTER),sizeof(MONITOR_CENTER));
        monitor_map[monitor->ID] = monitor;
    }
    printf("build monitor node map successful\n");

}
void SYSDATA::GetLimitData(char* data)
{
    COUNT cout_node;
    memcpy(&cout_node,data,sizeof(COUNT));
    for(int i = 0;i<cout_node.Count_Power;i++){
        LIMIT* lim = new LIMIT;
        memset(lim,0,sizeof(LIMIT));
        memcpy(lim,data+sizeof(COUNT)+i*sizeof(LIMIT),sizeof(LIMIT));
        if(lim->type == 1){       //属于权限组
            powergrp_map[lim->ID] = lim;
            power_map[lim->ID] = lim;
        }
        else{       //权限子项
            power_map[lim->ID] = lim;
            poweritem_map[lim->ID] = lim;
        }
    }
    printf("build power node map successful\n");
}


