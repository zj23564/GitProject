
#ifndef DEVICE_JOB_H
#define DEVICE_JOB_H


#include "include/ThreadPool/Job.h"
#include "include/data_define/Data_Define.h"



class Device_Job : public CJob
{
    public:
        Device_Job(int flag,DEVICE_DATA* data);
        virtual ~Device_Job();

        void Run(void * jobData);

    protected:
    private:
        conn_t * m_fd;
        int m_len;
        int m_flag;
        DEVICE_DATA* m_data;
};

#endif
