

#ifndef MEM_DATA_H_
#define MEM_DATA_H


#include <map>
#include <vector>
#include "../data_define/Data_Define.h"
using namespace std;
class MEM_DATA{

    public:
            MEM_DATA();
            ~MEM_DATA();
            char* Get_Device_Block();       //将数据库中所有的设备节点数据放入一个空间连续的内存快，返回内存快首地址
            char* Get_DeviceGroup_Block();
            char* Get_User_Block();         //将数据库中所有的用户数据节点放入一个空间连续的内存快，返回内存块首地址
            char* Get_Usergroup_Block();    //you know
            char* Get_LimitBlock();       //获取limit list
            char* Get_Device_Channel();
            char* Get_Monitor_Block();



            COUNT* Get_AllDev_Count(){return num;}
            USERCOUNT* Get_AllUser_Count(){return user_count;}



            int Search_User_PowerID(char*);         //用户登录时，查找该用户在数据库中的信息
            SendData*  User_Device(int);        //查找所有在该用户权限管辖范围内的设备节点
            SendData*  Ready_All_Device(){return All_Device;};          //准备好所有的设备数据 待发送

            char* Search_Device_Data(int);

            map<int,DEVICE_CHANNEL*>  DeviceChnnel_map;
            map<int,NODE_GRP*>  DeviceGrp_map;
            map<int,NODE*>        Device_map;
            map<int,LIMIT*>     Power_map;
            map<int,MONITOR_CENTER*>     monitor_map;
            map<string,USERINFO*>  User_map;
            vector<USERINFO*> user_vector;



    private:

            DEVICE* Device_Block;
            char* User_Block;
            char* Usergroup_Block;
            SendData*  All_Device;          //存放所有的设备节点的内存块起始地址和大小
            map<int,USERGROUP*> Usergroup_map;
            map<char*,USERINFO*>::iterator iter_user;

            COUNT* num;
            USERCOUNT* user_count;
};

#endif
