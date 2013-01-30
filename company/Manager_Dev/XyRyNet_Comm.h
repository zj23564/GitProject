#pragma once
//#include <ace/Time_Value.h>
//#include <ace/Handle_Set.h>
//#include <ace/Log_Msg.h>
//#include <ace/INET_Addr.h>
//#include <ace/SOCK_Connector.h>
//#include <ace/SOCK_Acceptor.h>
//#include <ace/SOCK_Stream.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <wchar.h>
#include <wctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <termios.h>
#include <semaphore.h>
#include <dirent.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string.h>
#include <stropts.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <sys/vfs.h>
#include <sys/sysinfo.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <net/if.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/mount.h>

#include "XyRyNet_Types.h"
using namespace std;
/********************************************************************
//	Created:	2011/9/14   15:14
//	Filename: 	WorkSpace/PtzServer/HT_Ptz_SerialPort/HT_Ptz_SerialPort/HT_QYT_Comm.h
//	File Path:	WorkSpace/PtzServer/HT_Ptz_SerialPort/HT_Ptz_SerialPort/
//	File Base:	HT_Ptz_SerialPort
//	File Ext:	h
//      Project:        HT_MonitoringCenter
//	Author:		dowflyon
//	Purpose:	公用头文件
//	History:
*********************************************************************/
///////////////////////////////////////////////////////////////////
//                  客户端数据结构公用头定义
///////////////////////////////////////////////////////////////////
/******************************************************************
                    一期数据结构
******************************************************************/
#define MAX_SEND_BUFFER 4076

typedef struct cacheDataList
{
     char data[MAX_SEND_BUFFER];
     long identifier;
     struct cacheDataList *next;
     //struct cacheDataList *pre;
}cacheList;

typedef struct tag_HT_Comm_PacketsOne         //公用头格式
{
     char startBit[5];                       //起始位
     long identifier;                          //唯一标识符
     int totalDataLength;                    //整个数据总长度

    struct                                 //发送缓冲区
    {
        int bufferLength;                 //本次要发送的数据总大小
        char szSendBuffer[MAX_SEND_BUFFER];           //要发送的缓冲区
    }HT_COMM_BUFFER;
}HT_COMMPACKETSONE,*LPHT_COMMPACKETSONE;
/******************************************************************
                    二期数据结构
******************************************************************/
#define HT_NETCENTER_PACKETTYPE_UNKNOW 0   //无法确定的包类型
#define HT_NETCENTER_PACKETTYPE_ACK 1      //确认包
#define HT_NETCENTER_PACKETTYPE_SEQ 2      //请求包，作为nMapType，请求一个szMoudelName名称的映射表ID信息，返回nClientID
#define HT_NETCENTER_PACKETTYPE_SYN 3      //同步包，作为nMapType，完整请求映射表信息
#define HT_NETCENTER_PACKETTYPE_FIN 4      //结束包，作为nMapType，请求映射表后，如果完成将返回此
#define HT_NETCENTER_PACKETTYPE_MAP_DEL 5  //删除包，映射表有离开消息，通知你离开的ID，由映射表中心发送给你的状态
#define HT_NETCENTER_PACKETTYPE_MAP_ADD 6  //添加包，映射表有加入消息，通知你添加的ID和模块名称，由映射表中心发送给你的状态
//数据集
typedef enum en_HT_Packets_Leave           //数据包等级
{
    HT_PACKET_LEAVE_LOW = 1,               //低优先级，低交互，低响应使用级别
    HT_PACKET_LEAVE_NORMAL,                //正常级别，命令通道使用级别
    HT_PACKET_LEAVE_HIGH,                  //高优先级，快速响应使用级别
    HT_PACKET_LEAVE_URGENT                 //紧急事件，报警信息等
}HT_PACKETLEAVE,*LPHT_PACKETLEAVE;
typedef enum en_HT_Packets_Type            //数据包类型
{
    HT_PACKET_TYPE_MOUDELMAP = 1,          //模块映射包
    HT_PACKET_TYPE_COMMAND = 2,            //命令包
    HT_PACKET_TYPE_DATAS                   //数据包
}HT_PACKETTYPE,*LPHT_PACKETTYPE;
//数据结构
typedef struct tag_HT_Comm_Packets         //公用头格式
{
    char DestSendAddr[24];                 //发送目标客户地址 格式 192.168.0.1:6000
    HT_PACKETLEAVE en_PacketLeave;         //数据包等级 取值 HT_PACKETLEAVE 等级排列：从小到大
    HT_PACKETTYPE nPacketType;             //包类型，映射包忽略除了 HT_MOUDEL_MAP 以外的信息
    struct                                 //发送缓冲区
    {
        char *pszSendBuffer;               //要发送的缓冲区
        int nBufferLength;                 //本次要发送的数据总大小
    }HT_COMM_BUFFER;
}HT_COMMPACKETS,*LPHT_COMMPACKETS;
typedef struct tag_HT_MoudelMap            //模块映射信息表
{
    char szMoudelName[24];                 //映射名称：报警服务器  WarnningServer
    unsigned int nClientID;                //映射ID号：53001
    unsigned int nMapType;                 //映射包类型
}HT_MOUDELMAP,*LPHT_MOUDELMAP;
/******************************************************************
                    三期数据结构
******************************************************************/
typedef struct tag_NetEngine_Client_TcpConfig
{
    unsigned int CachePoolTimedOut;         //缓冲池单包超时时间
    unsigned int CachePoolMaxPacket;        //缓冲池最大允许包数量
    unsigned int CachePoolMaxBuffer;        //缓冲池最大缓冲区大小
    unsigned int CachePoolMaxReSend;        //缓冲池最大允许重试发送次数
}NETENGINE_CLIENT_TCPCONFIG,*LPNETENGINE_CLIENT_TCPCONFIG;
///////////////////////////////////////////////////////////////////
//                  自定义类型
///////////////////////////////////////////////////////////////////
typedef unsigned long (DWORD);                           //双字
typedef const char * (LPCSTR);                           //ANSI常量字符指针
typedef const wchar_t * (LPWSTR);                        //UNICODE常量字符指针
typedef unsigned char (BYTE);                            //无符号字符
typedef bool BOOL;                                       //逻辑型
typedef pthread_t (HANDLE);                              //线程句柄
typedef int (HFILE);                                     //文件句柄
typedef void * (LPVOID);                                 //五类型指针
typedef int (SOCKET);                                    //网络套接字句柄
typedef unsigned char (uint8_t);                         //1个字节
typedef unsigned int (UINT);                             //无符号整数型

#define INVALID_HANDLE_VALUE -1                          //失败的文件句柄
#define INVALID_SOCKET -1                                //失败的SOCKET句柄
#define SOCKET_ERROR -1                                  //错误的SOCKET处理
#define FALSE 0
#define TRUE 1
#define MAXADDR 23

#define MAX_PATH 256
#define LPCTSTR LPCSTR
#define WCHAR wchar_t
#define CHAR char
#define TCHAR char
