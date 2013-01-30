#ifndef LOGDADA_DEFINE_H_INCLUDED
#define LOGDADA_DEFINE_H_INCLUDED

typedef struct HT_RETURN_LOG {
    int queryid;  //查询操作顺序号
    int logSearch; //日志类型
    int totalnum; //总共日志数
    int startnum; //日志起始数
    int datanum; //本次返回数量
} HT_RETURN_LOG;

typedef struct HT_READ_QUERY {
    int queryid;  //查询操作顺序号
    int queryFlag;  //标志是否查询所有日志  1，查询所有日志，2，根据其它参数判定查询日志
    int logSearch; //日志类型
   // int typegrp; //日志类型
    int  type;  //日志子类型
    int object; //对象
    int starttime;
    int endtime;
    int startnum; //读取开始位置
    int endnum; //读取结束位置
} HT_READ_QUERY;        //日志查询数据结构


//服务器回复的每个日志数据的数据结构
//全部以字符串的形式呈现
typedef struct _HT_LOG_ITEM{
    int list_num;   //日志序号
    int time;
  //  char typegrp[32];
    char type[64];
    char objtype[32];
    char obj[64];
    char context[256];
}HT_LOG_ITEM;

/****LogTypeGrp对应日志类型 LogType对应日志子类型*************/
typedef struct _LogObjType{
    int ID;
    int type;
    char name[32];
}LogObjType;

typedef struct LogType{
    int ID;
    int PID;        //如果类型还有分组，则可以这个字段
    int type_obj;    //该日志子类型对应的日志类型
    char name[64];  //日志名
}LogType;


#endif // LOGDADA_DEFINE_H_INCLUDED
