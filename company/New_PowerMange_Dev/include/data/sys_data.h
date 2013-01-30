#ifndef SYS_DATA_H_INCLUDED
#define SYS_DATA_H_INCLUDED

#include "Define_Data.h"
#include <map>

using namespace std;

class SYSDATA{

    public:
        SYSDATA();
        ~SYSDATA();
        void GetDeviceData(char* data);
        void GetUserData(char* data);
        void GetMonitorData(char*);
        void GetLimitData(char*);

        map<int,DEVICE*> dev_map;
        map<int,DEVICE_GRP*> devgroup_map;
        map<int,USERINFO*> user_map;
        map<int,DEVICE_CHANNEL*> devchn_map;
        map<int,MONITOR_CENTER*>monitor_map;
        map<int,LIMIT*>power_map;
        map<int,LIMIT*>powergrp_map;
        map<int,LIMIT*>poweritem_map;

        //主树结构上的设备树节点数据表
        map<int,TREEDATA*> tree_devGrpMap;
        map<int,TREEDATA*> tree_devMap;
        map<int,TREEDATA*> tree_limitMap;
        map<int,TREEDATA*> tree_chnMap;

        //用户专有树和设备专有树
        map<int,TREEDATA*>devTree_map;
        map<int,TREEDATA*>devgroupTree_map;
        map<int,TREEDATA*>userTree_map;

    private:


};



#endif // SYS_DATA_H_INCLUDED
