#ifndef DEFINE_PAGE_H_INCLUDED
#define DEFINE_PAGE_H_INCLUDED


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


/**************写入日志服务器的结构中的相关参数***********/
//int obj
#define LOG_OBJECT_USER 1   //用户对象
#define LOG_OBJECT_SERVER 2 //服务器对象
#define LOG_OBJECT_DEVICE 3 //设备对象
#define LOG_OBJECT_TEMPTY 4 //其它对象
//int typegrp;        //类型包括，事件，操作，报警，其它
#define LOG_TYPEGRP_EVENT   1   //事件
#define LOG_TYPEGRP_OPERATE 2   //操作
#define LOG_TYPEGRP_ALARM   3   //报警
#define LOG_TYPEGRP_TEMPTY  4   //其它

/***一下是用户操作的项目，属于操作中的子项,也是用户权限列表*****/
//int type
#define POWER_TYPE_IMAGE        0x00010001  //画面分割
#define POWER_TYPE_IMAGE_1      0x00010002  //  1画面分割
#define POWER_TYPE_IMAGE_4     0x00010003   //4画面分割
#define POWER_TYPE_IMAGE_9     0x00010004   //9画面分割
#define POWER_TYPE_IMAGE_16     0x00010005  //16画面分割

#define POWER_TYPE_VIDEO        0x00010006  //视频预览
#define POWER_TYPE_VIDEO_FULL     0x00010007    //  全屏切换
#define POWER_TYPE_VIDEO_TWO_SCREEN     0x00010008  //     二分频互换预览
#define POWER_TYPE_VIDEO_OSD     0x00010009 //  本地OSD叠加显示
#define POWER_TYPE_VIDEO_EFFECT     0x00010010  //  效果调节
#define POWER_TYPE_VIDEO_POLL     0x00010011    //  轮询

#define POWER_TYPE_PTZ            0x00010012        //云台控制
#define POWER_TYPE_PTZ_DIRECT     0x00010013    //  云台方向控制
#define POWER_TYPE_PTZ_SCAL     0x00010014  //      云台跳聚焦/光圈/缩放
#define POWER_TYPE_PTZ_WHEEL_GUARD     0x00010015   //  云台轮巡功能
#define POWER_TYPE_PTZ_LOCK     0x00010016  //  云台锁定/解锁
#define POWER_TYPE_PTZ_SETPOINT     0x00010017  //  云台预置点设置和调用

#define POWER_TYPE_LOGIN_LAYOUT     0x00010018  //登录与布局
#define POWER_TYPE_LOGIN_LAYOUT_LOGIN     0x00010019    //   用户登录
#define POWER_TYPE_LOGIN_LAYOUT_LOGINMEM     0x00010020 //  登录信息记忆
#define POWER_TYPE_LOGIN_LAYOUT_LAYOUTSAVE     0x00010021   //  主界面布局保存/使用/修改

#define POWER_TYPE_LOG      0x00010022//日志
#define POWER_TYPE_LOG_QUERY     0x00010023 //      查询日志
#define POWER_TYPE_LOG_BAK     0x00010024   //  日志备份
#define POWER_TYPE_LOG_RTIME_CTRL     0x00010025    // 实时日志控制
#define POWER_TYPE_LOG_ADDTYPE     0x00010026   //  增加日志类型

#define POWER_TYPE_VOIDE        0x00010027  //视频录像
#define POWER_TYPE_VOIDE_LOCAL     0x00010028   //  录像到本地
#define POWER_TYPE_VOIDE_SERVER     0x00010029  //  录像到服务器
#define POWER_TYPE_VOIDE_FRONT     0x00010030   //  前端录像
#define POWER_TYPE_VOIDE_MANUAL     0x00010031  //  手动录像
#define POWER_TYPE_VOIDE_TIMEING     0x00010032 //  定时录像
#define POWER_TYPE_VOIDE_ALARM     0x00010033   //  报警联动录像
#define POWER_TYPE_VOIDE_SET     0x00010034 //  录像配置
#define POWER_TYPE_VOIDE_MANUALCAP     0x00010035   //  手动抓拍
#define POWER_TYPE_VOIDE_TIMEINGCAP     0x00010036  //  定时抓拍
#define POWER_TYPE_VOIDE_DOWNLOAD     0x00010037    //  录像下载
#define POWER_TYPE_VOIDE_FRONT_UPLOAD     0x00010038    //  前端录像上传服务器

#define POWER_TYPE_MATRIX       0x00010039  //矩阵上墙
#define POWER_TYPE_MATRIX_LAYOUT_SET     0x00010040 //  矩阵布局控制
#define POWER_TYPE_MATRIX_INPUT_SET     0x00010041  //  矩阵输入控制
#define POWER_TYPE_MATRIX_OUTPUT_SET     0x00010042 //  矩阵输出控制
#define POWER_TYPE_MATRIX_POLL_OUTPUT_SET     0x00010043    //  轮询输出控制

#define POWER_TYPE_USER     0x00010044      //用户权限
#define POWER_TYPE_USER_GRP     0x00010045  //  用户组
#define POWER_TYPE_USER_MANAGER     0x00010046  //  用户管理
#define POWER_TYPE_USER_POWER_TYPE     0x00010047   //  权限类型控制

#define POWER_TYPE_STREAM       0x00010048  //流媒体转发
#define POWER_TYPE_STREAM_TREE     0x00010049   //  显示流媒体树
#define POWER_TYPE_STREAM_FORWARD     0x00010050    //  流媒体转发控制

#define POWER_TYPE_MAP      0x00010051      //电子地图
#define POWER_TYPE_MAP_BITMAP     0x00010052    //    引入位图地图
#define POWER_TYPE_MAP_VECTORMAP     0x00010053 //  引入矢量地图
#define POWER_TYPE_MAP_DEVPOSMARK     0x00010054    //  设备点标记（增加|修改|删除）
#define POWER_TYPE_MAP_ALARM_TWINKL     0x00010055  //  报警联动闪烁
#define POWER_TYPE_MAP_ALARM_VIDEO     0x00010056   //  报警联动视频弹出

#define POWER_TYPE_ALARM        0x00010058      //报警
#define POWER_TYPE_ALARM_MANAGER_INPUTDEV     0x00010059    //  报警设备管理——报警输入
#define POWER_TYPE_ALARM_MANAGER_OUTPUTSWC     0x00010060   //报警设备管理——报警输出
#define POWER_TYPE_ALARM_TYPE_MANAGER     0x00010061    //  报警类型管理
#define POWER_TYPE_ALARM_DEPLOY     0x00010062  //  撤布防
#define POWER_TYPE_ALARM_LINKAGE     0x00010063 //  报警联动点设置

#define POWER_TYPE_INTERCOM     0x00010064      //对讲
#define POWER_TYPE_INTERCOM_FRONT_BACK     0x00010065     //单点前后端对讲

#define POWER_TYPE_SOURCEDOWNLOAD   0x00010066  //资源下载
#define POWER_TYPE_SOURCEDOWNLOAD_FRONTVIDEO     0x00010067 //  前端视频下载
#define POWER_TYPE_SOURCEDOWNLOAD_SERVERVIDEO     0x00010068    //  服务端视频下载

#define POWER_TYPE_AUX      0x00010069      //辅助信息控制
#define POWER_TYPE_AUX_TITLEBAR     0x00010070  //  切换视频预览窗口标题栏
#define POWER_TYPE_AUX_CPU     0x00010071   //  CPU使用率
#define POWER_TYPE_AUX_MEM     0x00010072   //  内存使用率
#define POWER_TYPE_AUX_LOAD     0x00010073  //  负荷统计


#endif // DEFINE_PAGE_H_INCLUDED
