#include "HT_NET_Engine.h"

void NetInit();

void Event_Sys(conn_t *conn, int eventtype, void *context, int error);

void Event_Dev(conn_t *conn, int eventtype, void *context, int error);


//

//线程处理函数

void* Run_send(void* arg);//循环从发送队列中拿出数据，处理发送任务

//管理发送队列的线程
void* ManagerSend_queue(void* arg);

//管理各个服务器发送给本服务器的数据的队列
void* Manager_queue(void* arg);

//管理设备发送给本服务器的数据队列
void* Manager_Device_queue(void* arg);

//设备注册线程开启，处理设备发送来的数据和请求，设备有关任务全部由此开始
void* Device_reg(void* arg);

//定时扫描在线设备的线程
void* ScanOnlineDevice(void*arg);

//定时扫描在线设备，用于判断设备是否还是在线
void Scanf_Timer(int arg);







