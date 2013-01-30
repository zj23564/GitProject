

#define NET "192.168.1.56:3250"
#define NETNO_PORT   "192.168.1.56"

/*************************************************
标志结合TREEDATA数据结构使用，区分绑定在树结构中不同的数据
类型,主要用于用户点击树结构时，显示不同的界面,节点数据放在
TREEDATA中的data指针中，当标志为other的时候，data指针为4个
字节，可能会用于直接存放一个4字节的整形数据
**************************************************/
#define TREE_FLAG_USER      0x00001000
#define TREE_FLAG_USERGROUP     0x00001001
#define TREE_FLAG_DEVICE        0x00001002
#define TREE_FLAG_DEVICEGROUP        0x00001003
#define TREE_FLAG_OTHER         0x0000104          //这个用于在主树结构中不同于用户节点用户组节点和设备节点的标志
#define TREE_FLAG_POWERMANAGER      0x00001005      //权限项目管理
#define TREE_FLAG_MONITOR_CENTOR    0x00001006      //监控中心
#define TREE_FLAG_DEVICECHANNEL 0x00001007
#define TREE_FLAG_POWERGRP      0x00001008      //权限分组
#define TREE_FLAG_POWERITEM     0x00001009      //权限子项目

#define TREE_FLAG_USER_NODE     0x0000100a      //所有用户的根节点
#define TREE_FLAG_CENTOR_NODE   0x0000100b      //所有中心的根节点
#define TREE_FLAG_DEVICE_NODE   0x0000100c      //所有设备的根节点
#define TREE_FLAG_MONITOR_CENTOR_NODE 0x0000100d    //监控中心根节点
/************************************************/

/**以下标志为在增加设备节点时的标志，主要区分是点击在设备组中选中的增加设备节点，还是在点击在设备节点上选择的增加设备节点**/

#define TREE_FLAG_ADDDEV_AT_GRP     0x00002000
#define TREE_FLAG_ADDDEV_AT_DEV     0x00002001
/**************************************************/


/***********增加监控中心节点类型的类型定义***************/
#define TREE_FLAG_CENTER_CENTER      0       //下面可以挂载监控服务
#define TREE_FLAG_CENTER_MCS         1   //管理服务
#define TREE_FLAG_CENTER_STREAM      2   //流媒体服务
#define TREE_FLAG_CENTER_LOG         3   //日志服务
#define TREE_FLAG_CENTER_ALARM       4   //报警服务

/***************************************************/
/*********************************************
*   设备类型定义 品牌 对应DEVICE结构中的type
************************************************/
#define DEVICE_TYPE_HK      0x00000001      //海康
#define DEVICE_TYPE_GH      0x00000002      //冠辉
#define DEVICE_TYPE_HB      0x00000003      //汉邦
#define DEVICE_TYPE_DH      0x00000004      //大华
#define DEVICE_TYPE_JG      0x00000005      //捷高
#define DEVICE_TYPE_WD      0x00000006      //微蒂
#define DEVICE_TYPE_DJL     0x00000007      //德加拉
#define DEVICE_TYPE_WL      0x00000008      //网力

#define DEVICE_TYPE_SMOKE   0x00000101      //烟感设备
#define DEVICE_TYPE_LED     0x00000102      //LED
#define DEVICE_TYPE_LIGHT   0x00000103      //报警灯
