/*
 * Protocol.h
 *
 *  Created on: 2011-10-9
 *      Author: Administrator
 */


#ifndef PROTOCOL_H_
#define PROTOCOL_H_


/*************************************************************
 *
 *                 公共头
 *
 *************************************************************/
typedef struct _HEAD {
	unsigned long SysMark; // 系统标志
	unsigned long ModuleMark; // 模块标识
	unsigned long PackType; // 包类型
	unsigned int PackSize; // 包长度
	unsigned int DataSize; // 数据长度
	unsigned long SessionID; // 会话ID
	unsigned long Time; // 时间戳
	long   ResultCode;
} HEAD, *LPHEAD;

/*************************************************************
 *
 *                通用协议
 *
 *************************************************************/

/*************************************************************
 *
 *                报警协议
 *
 *************************************************************/
typedef struct _ALMPOST {
	unsigned int DeviceID; // 设备ID
	unsigned int Channel; // 通道号
	unsigned int ALMType; // 报警类型
	unsigned long Timestamp; // 报警时间
} ALMPOST, *LPALMPOST;

/*************************************************************
 *
 *               流媒体协议
 *
 *************************************************************/
typedef struct _MSSREQUESTVS {
	unsigned long DeviceID; // 设备ID
	unsigned long Channel; // 通道号
	bool Record; // 是否为录像数据
	unsigned char Recordtype; // 录像类型
	unsigned short Reserves; // 保留
	unsigned long RecordID; // 录像ID
} MSSREQUESTVS, *LPMSSREQUESTVS;

typedef struct _MSSRESPONSEVS {
	struct {
		unsigned short VSFormat; // 视频格式
		unsigned short Version; // 编解码器版本
		unsigned short Width; // 图像宽度
		unsigned short Height; // 图像高度
	} Video;
	struct {
		unsigned short ASFormat; // 音频格式
		unsigned short Version; // 编解码器版本
	} Audio;
	unsigned short Fps; // 帧率
} MSSRESPONSEVS, *LPMSSRESPONSEVS;

/*************************************************************
 *
 *                日志协议
 *
 *************************************************************/
typedef struct HT_LOG {
    int list_ID;        //由查询日志的时候，服务器填写，写日志的时候不需理会,为查询日志返回的日志顺序号
    int time;       //time
    //int typegrp;        //类型包括，事件，操作，报警，其它
    int type;        //组类型中的具体子类型
    int object;      //对象，
    int objectID;   //objID
    char name[64];  //对象名字，如果是服务器，将写入具体服务器ID加名字组合，如果是用户对象，则直接写入用户名备对象，4-表明是其它对象
    char content[256]; //context
} HT_LOG;



/*************************************************************
 *
 *                                  WEB协议
 *
 *************************************************************/

/*************************************************************
 *
 *                                管理中心协议
 *
 *************************************************************/

/*********************************************
 *                             用户登录
 *********************************************/
typedef struct _MCSUSERLOGIN {
	char UserName[16]; // 用户
	char PassWord[32]; // 密码
	char power;
	unsigned long RHT;
} MCSUSERLOGIN, *LPMCSUSERLOGIN;



/*********************************************
 *                             用户退出
 *********************************************/

/*********************************************
 *                             注册模块
 *********************************************/
typedef struct _MCSREGMODULE {
	unsigned long ModuleType; // 模块类型
	unsigned char ModuleName[16]; // 模块名称
} MCSREGMODULE, *LPMCSREGMODULE;

/*********************************************
 *                             注销模块
 *********************************************/

/*********************************************
 *                             获取权限
 *********************************************/
typedef struct _MCSREQUESTPOWER {
	unsigned char Name[16]; // 用户名称
	unsigned long Role; // 角色
	unsigned long long Power; // 权限
} MCSREQUESTPOWER, *LPMCSREQUESTPOWER;

/*********************************************
 *                             请求设备树
 *********************************************/
typedef struct _MCSREQUSETDEVICETREE {
	unsigned long TreeType; // 树类型
} MCSREQUSETDEVICETREE, *LPMCSREQUSETDEVICETREE;

/*********************************************
 *                             相应设备树
 *********************************************/
typedef struct _MCSRESPONSEDEVICETREE {
	unsigned long TreeID; // 树ID
	unsigned char TreeName[16]; // 树名称
	unsigned long TreeNodeCount; // 树节点数
} MCSRESPONSEDEVICETREE, *LPMCSRESPONSEDEVICETREE;

/*********************************************
 *                             设备树节点
 *********************************************/
typedef struct _MCSTREENODE {
	unsigned long TreeNodeID; // 树节点ID
	unsigned char TreeNodeName[16]; // 树节点名称
	unsigned long TreeNodeType; // 节点类型
	unsigned long power; // 树节点权限
	unsigned int left; // 树左值
	unsigned int right; // 树右值
	struct{
	    char IP[16];
	    unsigned int port;
	    } Node_info;
} MCSTREENODE, *LPMCSTREENODE;

/*************************************************************
 *                 存储协议
 *************************************************************/
typedef struct _STGOPENREQUEST {
	unsigned char FileName[256];
	unsigned long Attrib;
} STGOPENREQUEST, *LPSTGOPENREQUEST;

typedef struct _STGOPENRESPONSE {
	unsigned long FileID;
} STGOPENRESPONSE, *LPSTGOPENRESPONSE;

typedef struct _STGREADREQUEST {
	unsigned long FileID;
	unsigned long Size;
} STGREADREQUEST, *LPSTGREADREQUEST;

typedef struct _STGREADRESPONSE {
	unsigned long FileID;
	unsigned long DataSize;
} STGREADRESPONSE, *LPSTGREADRESPONSE;

typedef struct _STGWIRTE {
	unsigned long FileID;
	unsigned long Size;
} STGWIRTE, *LPSTGWIRTE;

/*************************************************************
 *                 云台协议
 *************************************************************/
typedef struct _PTZCONTROL {
	unsigned int DeviceID; // 设备ID
	unsigned char Command[8]; // 云台控制包
} PTZCONTROL, *LPPTZCONTROL;

typedef struct _PTZCONFIGDATA {
	unsigned long NetCenterIP; // 网络中心地址
	unsigned short NetCenterPort; // 网络中心端口
	unsigned long DataBaseIP; // 数据库服务器地址
	unsigned short DataBasePort; // 数据库服务器端口
	unsigned char DatabaseDBName[16]; // 数据库名称
	unsigned char DatabaseUserName[16]; // 数据库用户名
	unsigned char DatabaseUserPwd[16]; //数据库密码
} PTZCONFIGDATA, *LPPTZCONFIGDATA;

/*************************************************************
 *                 矩阵协议
 *************************************************************/

/*************************************************************
 *                智能分析协议(保留)
 *************************************************************/


#endif /* PROTOCOL_H_ */
