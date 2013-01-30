#ifndef DATA_DEFINE_H_INCLUDED
#define DATA_DEFINE_H_INCLUDED
#include "../../HT_NET_Engine.h"

typedef struct _QueueData
{
    unsigned long SysMark; // 系统标志
    unsigned long ModuleMark; // 模块标识
    unsigned long PackType; // 包类型
    char * Buf;
    int Buflen;
    conn_t * fd;
}QueueData;




/*********************device data  and  job data***********************/
typedef  struct _DEVICE_DATA{
        conn_t * fd;
        int len;
        char* buff;
      }DEVICE_DATA;

typedef struct _DEVICE_JOB_DATA{
        DEVICE_DATA* data;
        int flag;
      }DEVICE_JOB_DATA;



typedef struct _QueueSendData
{
  char *Send;
  conn_t * fd;
}QueueSendData;



  /******************************************************************
 *                 以下是 设备  设备组  公司   临时数据结构
 ******************************************************************/
 typedef struct _USERTIMER{
    int year;
    int month;
    int day;
 }USERTIMER,*LMPUSERTIMER;

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

 typedef struct _COUNT{
        int Count_Group;
        int Count_Device;
        int Count_Channel;
        int Count_Power;
        int Count_Stream;
}COUNT,*LPCOUNT;


 //专门用于在线设备的数据，
 typedef struct _LOG_DEVICE{
        DEVICE* device;
        int hart_nowtime;    //这次心跳包到达的时间
        conn_t * fd;      //上次心跳包到达的时间
 }LOG_DEVICE;

typedef struct _NODE{

        DEVICE device;
		_NODE* next;
		_NODE* pre;

	}NODE;

typedef struct _NODE_CHANNEL{
        DEVICE_CHANNEL channel;
        _NODE_CHANNEL * next;
        _NODE_CHANNEL *pre;
}NODE_CHANNEL ;

typedef struct _NODE_GRP{

        DEVICE_GRP device_grp;
		_NODE_GRP* next;
		_NODE_GRP* pre;

	}NODE_GRP;
	//用于链表结构




/******************用户信息********************/
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

typedef struct _USERCOUNT{
        int Count_User;
        int Count_Group;
}USERCOUNT,*LPUSERCOUNT;

typedef struct _MODIFY_PASSWD{
        char Oldpasswd[24];
        char passwd[24];
}MODIFY_PASSWD;

typedef struct _RESPONADDUSER{      //服务器回复主控端增加用户的数据结构
    USERINFO newUser;
}RESPONADDUSER;

typedef struct _DEVBELONGUSER{
    int num;    //统计这个设备赋予用户的个数
    int cn_num;
    char usr[512][16];   //用户名的数组
    char cancel_usr[512][16];   //修改设备信息时，取消管理设备管理权限的用户集
}DEVBELONGUSER;
/*******************删除用户***************/
typedef struct _DELUSER{
    char name[60];
    int ID;
}DELUSER,*LPDELUSER;

/*******************user power**************/
typedef struct _LIMIT{
    int ID;     //limit id
    int PID;
    int type;       //1 gourp limit  2limit item
    int able;       //0 disable   1 able
    char name[64];
}LIMIT;
/*************************************************************/

/******************************************/
typedef struct _SendData
{
  char *data;
  int len;
  COUNT* node_count;
}SendData;      //装入用户所能管辖的节点信息，包括总节点数据长度len，数据节点在内存中的起始地址data，和各个节点的数目.

typedef struct _MAP_USER_NAME{
    char name[60];
    SendData*  user_powerinfo;
}MAP_USER_NAME;             //新用户上线后对应的表节点，节点信息中包含名字和与他相关的设备数据

/***********流媒体服务器ip和端口********************/
typedef struct _MSSINFO{
    char IP[16];
    int port;
}MSSINFO;
/*******************************************/

//掉线设备信息数据结构
typedef struct _DEVICELOGOUT{
    int m_time;    //掉线时间
    int ID;             //掉线设备ID
    char name[64];      //掉线设备名字
}DEVICELOGOUT;
//扫描期间时段内设备掉线数量
typedef struct _DEVICELOGOUT_COUNT{
    int logout_count;
}DEVICELOGOUT_COUNT;

/*********获取各个服务器信息的结构体*********/
typedef struct __ServerInfo{
	char 	m_Addr[32];
	short 	m_Port;
	int		m_Reserve;
}ServerInfo;

typedef struct __ServerListInfo{
	ServerInfo m_AlarmServer;
	ServerInfo m_StreamServer;
	ServerInfo m_LogServer;
	ServerInfo m_TVWallServer;
	ServerInfo m_StorageServer;
}ServerListInfo;


#endif // DATA_DEFINE_H_INCLUDED
