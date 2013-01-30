#ifndef GLOBALFUNC_H_INCLUDED
#define GLOBALFUNC_H_INCLUDED
#include "net/HT_NET_Engine.h"
void Event_Sys(conn_t *conn, int eventtype, void *context, int error);
void ReceviedData(conn_t *conn, char *buf, int len, void *context);
void Request_Data(int mark,char* data,int data_len);
#endif // GLOBALFUNC_H_INCLUDED
