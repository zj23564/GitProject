

#include "../../include/send/SendObject.h"
#include <stdio.h>

//queue<QueueData*> ObjectFactoy::m_queue
SendObject::SendObject()
{

}
SendObject::SendObject(conn_t* fd,int len)
{
    Send_fd = fd;
    Send_len = len;
}



SendObject::~SendObject()
{
    printf("Recycling\n");
   delete  [] Sendbuff->Send;
   delete Sendbuff;

}

int send_count = 0;
void SendObject::Run(void* jobdata)
{

    Sendbuff = (QueueSendData*)jobdata;
    send_count++;
   // printf("send count is  >>>>>>>>>>>>>>>>>>>>      %d\n",send_count);
   printf("send data len is %d\n",Send_len);
    Tcp_SendMsg(Send_fd,Sendbuff->Send,Send_len);

}


