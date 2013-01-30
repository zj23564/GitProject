#ifndef LOG_DB_H
#define LOG_DB_H
#define db_insret 100
#define db_query 200
#include "log_define.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../netlib/HT_NET_Engine.h"
using namespace std;

extern int init_db(void);
extern int exti_db(void);
string query_limit(char* query);
int insert_db(void *htlog);
int query_db(void* htlog);
int query_db2(void* htlog);
int Deal_db_Switch(void*);

void GetLogTypeObj(void* msg);
void GetLogType(void* msg);
void RealTimeLogRequest(void* msg);

void AddSourceType(void* msg);
void AddLogType(void* msg);

void DelSourceType(void* msg);
void DelLogType(void* msg);

void SendDataToSys(conn_t* fd,int mark,int result,char* data,int len);
char* GetLocalIP();

#endif
