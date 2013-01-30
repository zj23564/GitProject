#ifndef DEFINE_LOG_H_INCLUDED
#define DEFINE_LOG_H_INCLUDED

#define LOG_OBJECT_USER 1   //用户对象
#define LOG_OBJECT_SERVER 2 //服务器对象
#define LOG_OBJECT_DEVICE 3 //设备对象
#define LOG_OBJECT_TEMPTY 4 //其它对象
//int typegrp;        //类型包括，事件，操作，报警，其它
#define LOG_TYPEGRP_EVENT   1   //事件
#define LOG_TYPEGRP_OPERATE 2   //操作
#define LOG_TYPEGRP_ALARM   3   //报警
#define LOG_TYPEGRP_TEMPTY  4   //其它




#define GET_LOG_ALL 0x10001000      //取得所有日志
#define GET_LOG_ONEPAGE 0x10001001  //取得一页日志


#endif // DEFINE_LOG_H_INCLUDED
