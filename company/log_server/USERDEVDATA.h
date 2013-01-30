#ifndef USERDEVDATA_H
#define USERDEVDATA_H
#include <map>
#include "Share_Data.h"
#include "netlib/HT_NET_Engine.h"
#include "include/log_define.h"

using namespace std;
void UserDevDataEvent(conn_t *conn, int eventtype, void *context, int error);
void ReceviedData(conn_t *conn, char *buf, int len, void *context);  //USERDEVDATA RECEIVE DATA FUNC

class USERDEVDATA
{
    public:
        USERDEVDATA(char* McsIp);
        void ReConnect_Mcs();
        void McsDataInit();
        void GetDevData(char* data);
        void GetUserData(char* data);
        void SetMcsfdNULL(){fd = NULL;}
        void Request_To_MCS(int mark,char* data,int data_len);
        virtual ~USERDEVDATA();
        map<int,USERINFO*> usr_map;
        map<int,DEVICE*> dev_map;
        map<int,DEVICE_CHANNEL*> channel_map;

        void GetLogTypeObjFromSql();
        void GetLogTypeFromSql();
        map<int,LogObjType*> LogTypeObj_map;
        map<int,LogType*> LogType_map;


    protected:
    private:
    conn_t* fd;
    char mscIP[16];
};

#endif // USERDEVDATA_H
