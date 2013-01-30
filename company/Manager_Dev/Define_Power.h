
/******主控台模块***************/

#define  CHECKPOWER_USER_LOG        //登录
#define  CHECKPOWER_USER_LOGOUT     //退出
#define  CHECKPOWER_USER_ADDUSER    3        //添加用户
#define  CHECKPOWER_USER_EDITUSER      4     //修改用户
#define  CHECKPOWER_USER_DELETEUSER   5  //删除用户

/******流媒体模块***************/
#define STREAM
#ifdef  STREAM

#define  CHECKPOWER_MSS_PREVIEW 1     //  视频预览
#define  CHECKPOWER_MSS_VIDEO  2        //录像
#define  CHECKPOWER_MSS_VIDEO_SEARCH  3     //录像查询
#define  CHECKPOWER_MSS_PLAYBACK    4       //回放
#define  CHECKPOWER_MSS_CAPTURE_LOCAL   //本地抓拍
#define  CHECKPOWER_MSS_CAPTURE_FRONT   //前端抓拍
#define  CHECKPOWER_MSS_DOWNLOAD_VIDEO  //录像下载
#define  CHECKPOWER_MSS_EDITOR_VIDEO    //录像编辑
#define  CHECKPOWER_MSS_DELETE_VIDEO    //录像删除

#endif


/*********日志模块***********/

#ifdef  LOG

#define   CHECKPOWER_LOG_QUERY         1    //查询日志

#endif

/************存储模块***********/

#ifdef STORAGE

#define

#endif
