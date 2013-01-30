#ifndef TOOLFUNCDEFINE_H_INCLUDED
#define TOOLFUNCDEFINE_H_INCLUDED

#include "../netlib/HT_NET_Engine.h"

void NetInit();


void  GetData(conn_t *conn, char *buf, int len, void *context);

void Event_Sys(conn_t *conn, int eventtype, void *context, int error);

void *db_thread_fun(void *arg);     //处理日志数据库操作的线程

void *hub_thread_fun(void *arg);//处理实时日志的线程

void Delete_RealTimeLogSocket(void* fd);

/******************mutex************/




#endif // TOOLFUNCDEFINE_H_INCLUDED
