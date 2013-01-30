#ifndef LOG_DATA_H_INCLUDED
#define LOG_DATA_H_INCLUDED

#define NET_PACKTYPE_LOG_GETLOGTYPEOBJ  0x00000304  //取得日志源类型
#define NET_PACKTYPE_LOG_GETLOGTYPE     0x00000305  //取得日志类型
#define NET_PACKTYPE_LOG_SREACH_REALTIMELOG 0x00000306  //查询实时日志


/******查询日志请求  请求包为 HEAD+HT_READ_QUERY******/
typedef struct HT_READ_QUERY {
    int queryid;  //查询操作顺序号，服务器填写
    int queryFlag;  //标志是否查询所有日志  1，查询所有日志，2，根据其它参数判定查询日志
    int logSearch; //日志类型
    int  type;  //日志类型
    int object; //对象
    int starttime;
    int endtime;
    int startnum; //读取开始位置，服务器填写，如果分页查询的要求，在下次查询请求发出时，需将这个值由查询方填入
    int endnum; //读取结束位置，服务器填写，如果分页查询的要求，在下次查询请求发出时，需将这个值由查询方填入
} HT_READ_QUERY;        //日志查询数据结构


/*************************************************
服务器回复的每个日志数据的数据结构
全部以字符串的形式呈现
最终服务器回复的日志信息数据为HEAD+HT_RETURN_LOG+HT_LOG_ITEM[日志数];
**************************************************/
typedef struct _HT_LOG_ITEM{
    int list_num;   //日志序号
    int time;
  //  char typegrp[32];
    char type[64];
    char objtype[32];
    char obj[64];
    char context[256];
}HT_LOG_ITEM;

/****接收到的实时日志数据为********
        HEAD+HT_LOG_ITEM
************************************/
/******日志返回的日志数据头******/
typedef struct HT_RETURN_LOG {
    int queryid;  //查询操作顺序号
    int logSearch; //日志类型
    int totalnum; //总共日志数
    int startnum; //日志起始数
    int datanum; //本次返回数量
} HT_RETURN_LOG;


/****写日志信息结构体*******/
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

/********************************************
****LogType对应日志类型LogObjType源类型
*****目前只有服务器使用，以后逐步推广到各个服务器使用*************/
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



#endif // LOG_DATA_H_INCLUDED
