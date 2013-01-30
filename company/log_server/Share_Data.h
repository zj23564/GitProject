#ifndef SHARE_DATA_H_INCLUDED
#define SHARE_DATA_H_INCLUDED
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


typedef struct _COUNT{
        int Count_Group;
        int Count_Device;
        int Count_Channel;
        int Count_Power;
        int Count_Stream;
}COUNT,*LPCOUNT;

typedef struct _USERCOUNT{
        int Count_User;
        int Count_Group;
}USERCOUNT,*LPUSERCOUNT;

/*********获取各个服务器信息的结构体*********/
typedef struct __ServerInfo{
	char 	m_Addr[32];
	short 	m_Port;
	int		m_Reserve;
}ServerInfo;
#endif // SHARE_DATA_H_INCLUDED
