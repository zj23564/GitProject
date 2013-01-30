/*
 * Platfrom.h
 *
 *  Created on: 2011-10-8
 *      Author: Administrator
 */

#ifndef PLATFROM_H_
#define PLATFROM_H_
#define HT_PLATFORM_RESULTCODE_SUCESS 0
/*********************************************
 *                系统标示
 *********************************************/
#define NET_SYSTEM_MASK_HTP   0x4854503E

/*********************************************
 *                模块标示
 *********************************************/
#define NET_MOUDLE_MASK_COM   0x00000100 // 通用协议
#define NET_MOUDLE_MASK_ALM   0x00000101 // 报警模块标示
#define NET_MOUDLE_MASK_MSS   0x00000102 // 流媒体模块标示
#define NET_MOUDLE_MASK_LOG   0x00000103 // 日志模块标示
#define NET_MOUDLE_MASK_WEB   0x00000104 // WEB模块标示
//#define NET_MOUDLE_MASK_MCS   0x000000110 // 管理中心模块标示
#define NET_MOUDLE_MASK_MCS     0x00000105  //模块指示中心
#define NET_MOUDLE_MASK_STG   0x00000106 // 存储模块标示
#define NET_MOUDLE_MASK_PTZ   0x00000107 // 云台模块标示
#define NET_MOUDLE_MASK_MTX   0x00000108 // 矩阵模块标示
#define NET_MOUDLE_MASK_SMT   0x00000109 // 智能某块标示
#define NET_MOUDLE_MASK_USER   0x0000010a  //用户登录
#define NET_MOUDLE_MASK_MAIN    0x0000010a

/*********************************************
 *                通用协议
 *********************************************/
#define NET_PACKTYPE_COM_FLASE              0x00000000 //
#define NET_PACKTYPE_COM_TRUE               0x00000001 //
#define NET_PACKTYPE_COM_SYNCONFIG          0x0000FF01 // 同步配置
#define NET_PACKTYPE_COM_SYNSESSION         0x0000FF02 // 同步会话列表

/*********************************************
 *                报警协议
 *********************************************/
#define NET_PACKTYPE_ALM_POST           0x00000100 // 投递报警消息
#define NET_PACKTYPE_ALM_REQUSET_GET    0x00000101 // 请求获取报警消息
#define NET_PACKTYPE_ALM_RESPONSE_GET   0x00000102 // 响应获取请求
#define NET_PACKTYPE_ALM_CHANNLEPOLICY  0x00000103 // 通道策略
#define NET_PACKTYPE_ALM_GETSTATUS      0x000001FD // 获取报警模块状态
#define NET_PACKTYPE_ALM_GETCONFIG      0x000001FE // 获取报警模块配置信息
#define NET_PACKTYPE_ALM_SETCONFIG      0x000001FF // 设置报警模块配置信息

/*********************************************
 *               流媒体协议
 *********************************************/
#define NET_PACKTYPE_MSS_REQUSET_VS     0x00000200 // 请求视频流
#define NET_PACKTYPE_MSS_RESPONSE_VS    0x00000201 // 响应视频请求
#define NET_PACKTYPE_MSS_GETSTATUS      0x000002FD // 获取流媒体模块状态
#define NET_PACKTYPE_MSS_GETCONFIG      0x000002FE // 获取流媒体模块配置信息
#define NET_PACKTYPE_MSS_SETCONFIG      0x000002FF // 设置流媒体模块配置信息

/*********************************************
 *                日志协议
 *********************************************/
#define NET_PACKTYPE_LOG_WRITE          0x00000300 // 写入日志
#define NET_PACKTYPE_LOG_REQUSE_QUERY   0x00000301 // 查询日志
#define NET_PACKTYPE_LOG_RESPONSE_QUERY 0x00000302 // 响应日志查询
#define NET_PACKTYPE_LOG_DOWNLOAD       0x00000303 // 下载日志
#define NET_PACKTYPE_LOG_GETLOGTYPEOBJ  0x00000304  //取得日志类型
#define NET_PACKTYPE_LOG_GETLOGTYPE     0x00000305  //取得日志子类型
#define NET_PACKTYPE_LOG_SREACH_REALTIMELOG 0x00000306  //查询实时日志
#define NET_PACKTYPE_LOG_ADDSOURCETYPE  0x00000307      //增加日志源类型
#define NET_PACKTYPE_LOG_DELSOURCETYPE  0x00000308      //删除日志源类型
#define NET_PACKTYPE_LOG_ADDLOGTYPE     0x00000309      //增加日志类型
#define NET_PACKTYPE_LOG_DELLOGTYPE     0x0000030A      //删除日志类型
#define NET_PACKTYPE_LOG_GETSTATUS      0x000003FD // 获取日志模块状态
#define NET_PACKTYPE_LOG_GETCONFIG      0x000003FE // 获取日志模块配置信息
#define NET_PACKTYPE_LOG_SETCONFIG      0x000003FF // 设置日志模块配置信息

/*********************************************
 *                 WEB协议
 *********************************************/
#define NET_PACKTYPE_WEB_GETSTATUS      0x000004FD // 获取WEB模块状态
#define NET_PACKTYPE_WEB_GETCONFIG      0x000004FE // 获取WEB模块配置信息
#define NET_PACKTYPE_WEB_SETCONFIG      0x000004FF // 设置WEB模块配置信息

/*********************************************
 *               管理中心协议
 *********************************************/
#define NET_PACKTYPE_MCS_REQUSET_REGMOUDLE     0x00000500 // 模块注册
#define NET_PACKTYPE_MCS_RESPONSE_REGMOUDLE    0x00000501 // 响应模块注册
#define NET_PACKTYPE_MCS_UNREGMOUDLE           0x00000502 // 模块取消注册
#define NET_PACKTYPE_MCS_REQUSET_USERLOGIN     0x00000503 // 用户登录
#define NET_PACKTYPE_MCS_RESPONSE_USERLOGIN    0x00000504 // 响应登录
#define NET_PACKTYPE_MCS_USERLOGOUT            0x00000505 // 用户退出
#define NET_PACKTYPE_MCS_REQUSET_QUERYSESSION  0x00000506 // 查询会话
#define NET_PACKTYPE_MCS_RESPONSE_QUERYSESSION 0x00000507 // 响应会话查询
#define NET_PACKTYPE_MCS_REQUSET_QUERYPOWER    0x00000508 // 查询权限
#define NET_PACKTYPE_MCS_RESPONSE_QUERYPOWER   0x00000509 // 响应权限查询
#define NET_PACKTYPE_MCS_REQUEST_DEVICETREE    0x0000050A // 请求设备树
#define NET_PACKTYPE_MCS_RESPONSE_DEVICETREE   0x0000050B // 响应设备树
#define NET_PACKTYPE_MCS_ADDUSER               0x0000050C // 添加用户
#define NET_PACKTYPE_MCS_DELETEUSER            0x0000050D // 删除用户
#define NET_PACKTYPE_MCS_MODIFYPASSWORD        0x00000517 // 修改密码
#define NET_PACKTYPE_MCS_EDITUSER              0x0000050E // 修改用户
#define NET_PACKTYPE_MCS_ADDGROUP               0x0000050F // 添加用户组
#define NET_PACKTYPE_MCS_DELETEGROUP            0x00000510 // 删除用户组
#define NET_PACKTYPE_MCS_EDITROLE              0x00000511 // 修改角色
#define NET_PACKTYPE_MCS_ADDDEVICE             0x00000512 // 添加设备
#define NET_PACKTYPE_MCS_DELETEDEVICE          0x00000513 // 删除设备
#define NET_PACKTYPE_MCS_EDITDEVICE            0x00000514 // 修改设备
#define NET_PACKTYPE_MCS_QUEST_DEVICESTATUS            0x00000515  //请求设备状态信息
#define NET_PACKTYPE_MCS_REQUEST_DEVICESTATU              0x00000516  //响应设备状态信息
#define NET_PACKTYPE_MCS_QUEST_MSSINFO             0x00000518  //流媒体服务器送达ip和端口信息
#define NET_PACKTYPE_MCS_REQUEST_MSSINFO             0x00000519
#define NET_PACKTYPE_MCS_NOTICE_DEVICE_ALARM        0x0000051A      //用户掉线报警
#define NET_PACKTYPE_MCS_QUEST_POWER_TREE           0x0000051B      //quest user power tree
#define NET_PACKTYPE_MCS_REQUEST_POWER_TREE           0x0000051C      //quest user power tree
#define NET_PACKTYPE_MCS_RESPONSEUSERS    0x000005FD // 获取用户树
#define NET_PACKTYPE_MCS_GETCONFIG             0x000005FE // 获取管理中心模块配置信息
#define NET_PACKTYPE_MCS_SETCONFIG             0x000005FF // 设置管理中心模块配置信息
#define NET_PACKTYPE_MCS_GETDEVINFO            0x00000601   //获取设备信息
#define NET_PACKTYPE_MCS_ADDDEVGRP              0x00000602  //增加设备分组请求
#define NET_PACKTYPE_MCS_DELDEVGRP              0x00000603  //删除设备分组
/***********************************************/

/*********************************************
 *                 存储协议
 *********************************************/
#define NET_PACKTYPE_STG_OPEN       0x00000600 // 打开文件
#define NET_PACKTYPE_STG_CLOSE      0x00000601 // 关闭文件
#define NET_PACKTYPE_STG_READ       0x00000602 // 读取
#define NET_PACKTYPE_STG_WIRTE      0x00000603 // 写入
#define NET_PACKTYPE_STG_FIND       0x00000604 // 查找文件
#define NET_PACKTYPE_STG_LIST       0x00000605 // 列出文件
#define NET_PACKTYPE_STG_DOWNFILE   0x00000606 // 下载文件
#define NET_PACKTYPE_STG_GETSTATUS  0x000006FD // 获取存储模块状态
#define NET_PACKTYPE_STG_GETCONFIG  0x000006FE // 获取存储模块配置信息
#define NET_PACKTYPE_STG_SETCONFIG  0x000006FF // 设置存储模块配置信息

/*********************************************
 *                 云台协议
 *********************************************/
#define NET_PACKTYPE_PTZ_COMMAND        0x00000700 // 云台控制
#define NET_PACKTYPE_PTZ_GETSTATUS      0x000007FD // 获取云台模块状态
#define NET_PACKTYPE_PTZ_GETCONFIG      0x000007FE // 获取云台模块配置信息
#define NET_PACKTYPE_PTZ_SETCONFIG      0x000007FF // 设置云台模块配置信息

/*********************************************
 *                 矩阵协议
 *********************************************/
#define NET_PACKTYPE_MTX_QUERYSTATUS    0x00000800 // 查询矩阵显示状态
#define NET_PACKTYPE_MTX_GETSTATUS      0x000008FD // 获取矩阵模块状态
#define NET_PACKTYPE_MTX_GETCONFIG      0x000008FE // 获取存储模块配置信息
#define NET_PACKTYPE_MTX_SETCONFIG      0x000008FF // 设置存储模块配置信息

/*********************************************
 *                智能分析协议(保留)
 *********************************************/
#define NET_PACKTYPE_SMT                0x00000900 //

#endif /* PLATFROM_H_ */
