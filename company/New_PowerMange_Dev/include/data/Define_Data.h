#ifndef DEFINE_DATA_H_INCLUDED
#define DEFINE_DATA_H_INCLUDED

 #include <wx/treectrl.h>

 /******************************************************************
 *                 以下是 设备  设备组  公司   临时数据结构
 ******************************************************************/

 //监控中心节点数据结构
 typedef struct _MONITOR_CENTER{
    int ID;
    int PID;
    int lev;
    int type;       //监控中心节点，或者监控中心下属的日志中心，报警中心，管理中心，流媒体中心等等
    int port;       //网络端口，如果是监控中心节点，无用
    char name[64];
    char IP[16];        //节点IP，如果是监控中心节点，为空
}MONITOR_CENTER;

typedef struct _USERTIMER{
    int year;
    int month;
    int day;
 }USERTIMER,*LMPUSERTIMER;

 typedef struct _DEVICE{
        char name[64];
        int ID;
        int group_ID;
        int type;       //品牌
        int status;

        /***********/
        char sys_num[32];        //设备编号，自定义规则编号
        char model[32];     //型号
        /***********/
        int port;
        char IP[32];
 }DEVICE,*LPDEVICE;

  typedef struct _DEVICE_CHANNEL{
        int ID;
        int chn_num;
        int group_ID;
        int status;
        char name[64];
  }DEVICE_CHANNEL;

 typedef struct _DEVICE_GRP{
        char name[64];
        int ID;
        int PID;
        int lev;        // 分组的级别，从1开始，理论上无限延伸
 }DEVICE_GRP,*LPDEVICE_GRP;

 /*****设备***************/
 typedef struct _DEVICE_INFO{
        char sys_num[16];       //系统统一编号
        int dev_ID;
        char IP[24];
        int port;
        /*新增数据类型*/
        int type_device;        //用户区分是设备节点还是设备分类节点
        int device_state;       //设备状态(合格，报修，停用，报废....)
        char brand[32];     //品牌
        char model[32];     //设备型号
        char manufacturer[32];  //生产厂家
        char factory_number[32];       //生产编号
        USERTIMER date_of_delivery;      //出厂日期
        USERTIMER date_of_purchase;  //购买日期
        char admin_department[32];  //管理部门
        char manager_person[32];    //负责人
        char install_position[64];  //安装位置
 }DEVICEINFO,*LPDEVICEINFO;

typedef struct _COUNT{
        int Count_Group;
        int Count_Device;
        int Count_Channel;
        int Count_Power;
        int Count_Stream;
}COUNT,*LPCOUNT;

/******************用户信息********************/

/************************设置用户权限*******************************
  规则说明：
  32位数据，每一位处理一个权限，从低到高依次是：
  主控台相关权限：
  0，设置登录权限；1，设置退出权限；2，设置添加用户权限；3，设置修改用户权限；
  4，设置删除权限
  流媒体相关权限：
  0，预览权限；1，录像权限；2，录像查询权限；3，回放权限；4，本地抓拍权限；
  5，前端抓拍权限；6，录像下载；7，录像编辑权限；8，录像删除权限；
  日志相关权限：
  0，查看日志权限；
******************************************************************/


typedef struct _USERINFO {
	char Name[32]; // 用户
	char PassWord[16]; // 密码
    int Type;       //1表示用户节点，2表示用户组节点
    int ID;              //用户ID ，由服务器给定，不能自定义
    int PID;           //用户所属组的ID ，可以没有，没有默认为0
    int lev;            //用户所属等级
    char power_ID[512];      //用于定位到该用户在他所属级别中的具体能操控的对象
    char power_dev[512];        //在该用户管辖范围内的设备节点ID集合
} USERINFO,*LPMUSERINFO;

typedef struct _USERGROUP{
  char Name[60]; // 用户
  char title[16];
  char PassWord[24]; // 密码
  int Type;       //1表示用户节点，2表示用户组节点
  int ID;              //用户ID ，由服务器给定，不能自定义
  int PID;           //用户所属组的ID ，可以没有，没有默认为0
  int power_ID;      //用于定位到该用户在他所属级别中的具体能操控的对象
  int lev;            //用户所属等级
  int power_Gstation;    //用户组的主控台权限
  int power_Gstream;   //用户组的流媒体权限
  int power_Glog;        //用户组的日志权限
  int power_Gother;    //用户组的其它权限
}USERGROUP,*LPMUSERGROUP;

typedef struct _DEVBELONGUSER{
    int num;    //统计这个设备赋予用户的个数
    int cn_num; //取消设备管理的用户个数
    char usr[512][16];   //用户名的数组
    char cancel_usr[512][16];   //修改设备信息时，取消管理设备管理权限的用户集
}DEVBELONGUSER;

/*******************user power**************/
typedef struct _LIMIT{
    int ID;     //limit id
    int PID;
    int type;       //1 gourp limit  2limit item
    int able;   //0 不可以选择  1 可以选择
    char name[64];
}LIMIT;

typedef struct _RESPONADDUSER{      //服务器回复主控端增加用户的数据结构
    USERINFO newUser;
}RESPONADDUSER;


typedef struct _DELUSER{
    char name[60];
    int ID;
}DELUSER,*LPDELUSER;

typedef struct _USERCOUNT{
        int Count_User;
        int Count_Group;
}USERCOUNT,*LPUSERCOUNT;

/*********************************************/

struct Tree_User{
    wxTreeItemId ID;
    USERINFO user;
    int sel;          //用于存放组列表的各个组的编号
};

struct Tree_Device{
    DEVICE device;
    wxTreeItemId ID;
};
struct Tree_DeviceGrp{
    DEVICE_GRP dev_grp;
    wxTreeItemId ID;
};

struct Tree_DeviceChn{
    DEVICE_CHANNEL dev_chn;
    wxTreeItemId ID;
};

struct Tree_Power{
    LIMIT power;
    wxTreeItemId ID;
};

struct Tree_Monitor{
    MONITOR_CENTER monitor;
    wxTreeItemId ID;
};

typedef struct _MSSINFO{
    char IP[16];
    int port;
}MSSINFO;

/*****用户作为帮定在主树结构中的数据的通用接口，data为帮定在树结构中主要的数据的地址指针，flag用于
******区分出是哪种数据，例如区分是设备数据还是用户数据，flag标志的宏定义在Define_Page.h中******/
//typedef struct _TREEDATA{
//    int flag;           //标志节点是什么节点  用户  设备  设备组 用户组
//    char* data;
//}TREEDATA;
typedef struct _TREEDATA{
    char* data;
    int flag;           //标志节点是什么节点  用户  设备  设备组 用户组
    wxTreeItemId ID;
}TREEDATA;

#endif // DEFINE_DATA_H_INCLUDED
