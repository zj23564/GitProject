
#ifndef SENDOBJECT_H
#define SENDOBJECT_H

#include "../ThreadPool/Job.h"
#include "../data_define/Protocol.h"

#include "../../include/data_define/Data_Define.h"

class SendObject : public CJob
{
    public:
        SendObject(conn_t* fd,int len);
        SendObject();
        virtual ~SendObject();

        void Run(void * jobData);

    protected:
    private:

      QueueSendData* Sendbuff;
      //char* Send_IP;
      conn_t* Send_fd;
      int Send_len;

};

#endif
