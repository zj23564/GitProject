#ifndef LOG_DEFINE_H
#define LOG_DEFINE_H

#define LOG_LOGTYPE_OP 1
#define LOG_LOGTYPE_EVENT 2

#define LOG_TYPE_INFO 1
#define LOG_TYPE_WARN 2

#define LOG_OBJECT_USER 1   //用户对象
#define LOG_OBJECT_SERVER 2 //服务器对象
#define LOG_OBJECT_DEVICE 3 //设备对象
#define LOG_OBJECT_TEMPTY 4 //其它对象

//#define LOG_TYPEGRP_TEMPTY  4   //其它
typedef struct DB_MSG {
    int datalen; /* db_insert db_query*/
    int sid;        //套接口
    void *msg;  //日志消息
} DB_MSG;

typedef struct HT_LOG {
    int list_ID;        //由查询日志的时候，服务器填写，写日志的时候不需理会,为查询日志返回的日志顺序号
    int time;       //time
    int type;        //组类型中的具体子类型
    int object;      //对象，
    int objectID;   //objID
    char name[64];  //对象名字，如果是服务器，将写入具体服务器ID加名字组合，如果是用户对象，则直接写入用户名备对象，4-表明是其它对象
    char content[256]; //context
} HT_LOG;



/********************************************************************************************/
/********************************************************************************************/


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


typedef struct HT_RETURN_LOG {
    int queryid;  //查询操作顺序号
    int logSearch; //日志类型
    int totalnum; //总共日志数
    int startnum; //日志起始数
    int datanum; //本次返回数量
} HT_RETURN_LOG;


/********************************************
****LogType对应日志类型LogObjType源类型*************/
typedef struct LogObjType{
    int ID;
    int type;
    char name[32];
}LogObjType;        //object type

typedef struct LogType{
    int ID;
    int PID;        //如果类型还有分组，则可以这个字段
    int type_obj;    //该日志子类型对应的日志类型
    char name[64];  //日志名
}LogType;


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
#endif
