#ifndef WRITE_LOG_H_INCLUDED
#define WRITE_LOG_H_INCLUDED
#include "../../HT_NET_Engine.h"
#include "../data_define/Protocol.h"

void Event_Sys_Log(conn_t *conn, int eventtype, void *context, int error);
void ReceviedData_Log(conn_t *conn, char *buf, int len, void *context);

conn_t* WriteLogNetInit(char* serverIP,int port);

/**********************************************************************************
modular:自己的模块标示  type:日志类型，就是各个服务器汇总的那些日志类型，将自己
各个模块写入与自己服务器相关的日志类型，object：写入自己的对象相应的编号
object:1，用户;2:报警服务器；3，流媒体服务器；4：存储服务器；5：日志服务器；6：其它
objectID：现在除了用户需要填入自己的sessionID,其余服务器目前为缺省值0；
name:缺省NULL  不用填，以后用
result:处理结果，字符串标示，如果不填，缺省NULL（需要填）
do_what:做的具体事情内容，字符串标示，如果不填，缺省NULL（需要填）
IP：可以输入，如果不填，将会默认为本地IP
有 content：处理结果：做了什么事，本地IP（缺省本地IP，也可输入）
*********************************************************************************/
int WriteLogToLogServer_C(conn_t* fd,int modular,int type,int object,int objectID,char* name,char*result,char* do_what,char* IP);

int GetTime();
char* GetLocalIP();
#endif // WRITE_LOG_H_INCLUDED
