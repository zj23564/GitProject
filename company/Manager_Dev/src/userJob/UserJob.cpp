#include "../../include/userJob/UserloginJob.h"
#include "../../HT_Platform_ResultCode.h"
#include "../../include/define/Define_Page.h"
#include "../../include/log/log_data.h"
#include "../../include/log/write_log.h"
#include <iostream>


extern MYSQL mysql;
using namespace std;
extern ObjectFactoy *m_fator;
void UserloginJob::MCS_USER(unsigned long packType)
{
    printf("package type is %x\n",packType);
    switch (packType){

            case NET_PACKTYPE_MCS_REQUSET_REGMOUDLE:     //模块注册
            {
                break;
            }
            case NET_PACKTYPE_MCS_UNREGMOUDLE:           //取消模块注册
            {
                break;
            }
            case NET_PACKTYPE_MCS_USERLOGOUT:
            {
                   printf("用户申请退出登录\n");
                Request_Logout();
                break;
            }
            case NET_PACKTYPE_MCS_REQUEST_DEVICETREE:       //请求设备树
            {
                Request_Device();
                break;
            }
            case NET_PACKTYPE_MCS_REQUSET_QUERYSESSION:     //查询会话
            {
                break;
            }
            case NET_PACKTYPE_MCS_REQUSET_QUERYPOWER:       //查询权限
            {
                printf("权限查询\n");
                Query_Power();
                break;
            }
            case NET_PACKTYPE_MCS_REQUSET_USERLOGIN:
            {
                User_Login();
               break;
            }
            case NET_PACKTYPE_MCS_ADDUSER:          //新增用户
            {
                    printf("print here\n");
                    break;
            }
            case NET_PACKTYPE_MCS_MODIFYPASSWORD:     //密码修改
            {
                printf("修改密码\n");
                Modify_passwd();
                break;
            }
            case NET_PACKTYPE_MCS_DELETEUSER:       //删除用户
            {
                DELUSER deluser;
                MCSUSERLOGIN log;
                memcpy(&log,qdata->Buf+sizeof(HEAD),sizeof(MCSUSERLOGIN));
                memcpy(&deluser,(qdata->Buf)+sizeof(HEAD)+sizeof(MCSUSERLOGIN),sizeof(DELUSER));
                printf("deluser is %s\n",deluser.name);
                char terminal[512];
                sprintf(terminal,"delete from user where name='%s';",deluser.name);     //删除行
                mysql_query(&mysql,terminal);
                cout<<"DEL USER  "<<endl;
                break;
            }
            case NET_PACKTYPE_MCS_ADDGROUP:
            {
              printf("增加用户组\n");

              break;
            }
            case NET_PACKTYPE_MCS_QUEST_POWER_TREE:
            {
                Requset_PowerTree();
                break;
            }
            case NET_PACKTYPE_MCS_QUEST_DEVICESTATUS:
            {
                Request_DeviceStatus();
                break;
            }
            case NET_PACKTYPE_MCS_GETSERVERLISTINFO:
            {
                Request_ServerInfo();
                break;
            }

            default:
                printf("application error\n");
    }
}

void UserloginJob::User_Login()
{
    int result  = Check_User();
    Request_Data(NET_PACKTYPE_MCS_RESPONSE_USERLOGIN,NULL,result,session_ID,sizeof(HEAD));
}

/*****************************************
*       1  表示登录成功    2表示没有这个用户
*       3  表示密码错误
******************************************/

int UserloginJob::Check_User()
{

    int size = m_fator->m_MemData.user_vector.size();
    MCSUSERLOGIN* c_usr = (MCSUSERLOGIN*)((qdata->Buf)+sizeof(HEAD));
    string str(c_usr->UserName);
    printf("user name is %s  passwd is %s\n",c_usr->UserName,c_usr->PassWord);
    USERINFO* usr = m_fator->m_MemData.User_map[str];
    if(NULL != usr){
        if(strcmp(usr->PassWord,c_usr->PassWord) == 0){
                 printf("done\n");
                session_ID++;
                m_fator->login_user[session_ID]  = usr;
                printf("new user session ID %d\n",session_ID);
                conn_t* log_fd = m_fator->GetLogSocket();

                if(log_fd != NULL){
                    int mark = 10019;
                    WriteLogToLogServer_C(log_fd,NET_MOUDLE_MASK_MCS,mark,1,usr->ID,NULL,"成功","login",NULL);
                }
                else
                    printf("log servers closed\n");
                printf("are you come back\n");
                return  HT_PLATFORM_RESULTCODE_SUCESS;
        }
        else{
                 printf("passwd error\n");
                return  HT_PLATFORM_RESULTCODE_ERRORPSWD;
        }
    }
    printf("no such user\n");
    return  HT_PLATFORM_RESULTCODE_NOUSER;
}

//用户退出
void UserloginJob::Request_Logout()
{
    int session = ((LPHEAD)qdata->Buf)->SessionID;
    int result = 10;
    if(m_fator->login_user[session] != NULL)
    {
        USERINFO* tmp = m_fator->login_user[session];
        m_fator->login_user.erase(session);
        result = HT_PLATFORM_RESULTCODE_SUCESS;
        printf("用户退出成功\n");
    }
    else
    {
            printf("一直都没有这个用户\n");
            result = HT_PLATFORM_RESULTCODE_NOUSER;
    }
    Request_Data(NET_PACKTYPE_MCS_USERLOGOUT,NULL,result,session,0);

}

void UserloginJob::Request_ServerInfo()
{
    ServerListInfo servers;
    memset(&servers,0,sizeof(ServerListInfo));

    memcpy(&servers.m_AlarmServer,m_fator->GetAlarmServerInfo(),sizeof(ServerInfo));

    memcpy(&servers.m_LogServer,m_fator->GetLogServerInfo(),sizeof(ServerInfo));

    memcpy(&servers.m_StorageServer,m_fator->GetStorageServerInfo(),sizeof(ServerInfo));

    memcpy(&servers.m_StreamServer,m_fator->GetStreamServerInfo(),sizeof(ServerInfo));

    memcpy(&servers.m_TVWallServer,m_fator->GetTVWallServerInfo(),sizeof(ServerInfo));

    Request_Data(NET_PACKTYPE_MCS_GETSERVERLISTINFO,(char*)&servers,HT_PLATFORM_RESULTCODE_SUCESS,0,sizeof(ServerListInfo));
}
























