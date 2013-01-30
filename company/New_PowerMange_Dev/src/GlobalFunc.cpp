#include "../include/GlobalFunc.h"
#include "../include/Tree/CGreatTree.h"
#include "../include/define/Define_Page.h"
#include "../include/data/Define_Data.h"
#include "../include/define/Define.h"
#include <wx/log.h>
extern New_PowerMangerFrame* Frame;

void Event_Sys(conn_t *conn, int eventtype, void *context, int error)
{
    printf("client event\n");
}
void Request_Data(int mark,char* data,int data_len)
{
        char* buff = NULL;
        int len = 0;
        HEAD head;
        head.SysMark = NET_SYSTEM_MASK_HTP;
        head.ModuleMark = NET_MOUDLE_MASK_MCS;
        head.PackType = mark;
        head.SessionID = 1;
        len = sizeof(HEAD)+data_len;
        buff = new char[len];
        memcpy(buff,&head,sizeof(HEAD));
        if(data != NULL){
            memcpy(buff+sizeof(HEAD),data,data_len);
        }
        printf("buff len is  %d\n",len);
        Tcp_SendMsg(Frame->Get_Connect(),buff,len);
        delete [] buff;
}

void ReceviedData(conn_t *conn, char *pzbuff, int len, void *context)
{
   // printf("----------------rcv data  len is %d, pzbuff = %p\n",len, pzbuff);
        if(NULL == pzbuff){
            printf("The server has disconnected\n");
            return;
        }
        HEAD *head = (HEAD*)pzbuff;

        if(head->SysMark==NET_SYSTEM_MASK_HTP){
            switch(head->PackType){
                case NET_PACKTYPE_MCS_RESPONSE_DEVICETREE:
                {

                    Frame->sys_data.GetDeviceData(pzbuff+sizeof(HEAD)+sizeof(MSSINFO));
                    CGreatTree tree(Frame,Frame->GetTreeCtrl1(),Frame->GetTreeDeviceParentID(),1);
                    tree.CreatDevTree();
                    CGreatTree tree1(Frame,Frame->GetTreeCtrl_DevTree(),Frame->GetTreeUserDevParentID(),2);
                    tree1.CreatDevTree();     //用户界面的树结构  先屏蔽

                    Request_Data(NET_PACKTYPE_MCS_RESPONSEUSERS,NULL,0);
                    break;
                }
                case NET_PACKTYPE_MCS_RESPONSEUSERS:
                {
                  printf("creat user tree   d\n");

                  Frame->sys_data.GetUserData(pzbuff+sizeof(HEAD));

                  CGreatTree tree(Frame,Frame->GetTreeCtrl1(),Frame->GetTreeUserParentID(),1);
                  tree.CreatUserTree();

                  CGreatTree tree1(Frame,Frame->GetTreeCtrl_UserTree(),Frame->GetTreeDevUserParentID(),2);
                  tree1.CreatUserTree();
                  Request_Data(NET_PACKTYPE_MCS_QUEST_POWER_TREE,NULL,0);

                  break;
                }
                case NET_PACKTYPE_MCS_ADDUSER:
                {
                    if(head->ResultCode == 0){
                        wxLogWarning(wxT("增加用户成功"));
                        Frame->SetNewUserOnTree(pzbuff+sizeof(HEAD));
                    }
                    else
                        wxLogWarning(wxT("增加用户失败"));

                    break;
                }
                case NET_PACKTYPE_MCS_EDITUSER:
                {
                    Frame->SetModifyUserOnTree(pzbuff+sizeof(HEAD));
                    break;
                }
                case NET_PACKTYPE_MCS_GETDEVINFO:
                {
                  //  Frame->Show_DeviceInfo((DEVICEINFO*)(pzbuff+sizeof(HEAD)));
                    break;
                }
                case NET_PACKTYPE_MCS_ADDDEVGRP:        //回复增加设备组节点
                {
                    DEVICE_GRP* dev_grp = (DEVICE_GRP*)(pzbuff+sizeof(HEAD));
                    Frame->SetNewDevGrpOnTree((char*)dev_grp);
                    break;
                }
                case NET_PACKTYPE_MCS_ADDDEVICE:
                {
                    printf("recvied add new dev\n");
                     Frame->SetNewDevOnTree(pzbuff+sizeof(HEAD));
                    break;
                }
                case NET_PACKTYPE_MCS_EDITDEVICE:
                {
                     printf("recvied edit dev\n");
                     Frame->UpdateDevOnTree(pzbuff+sizeof(HEAD));
                     break;

                }
                case NET_PACKTYPE_MCS_REQUEST_POWER_TREE:
                {
                    printf("recevied power tree data\n");
                    Frame->sys_data.GetLimitData(pzbuff+sizeof(HEAD));

                    CGreatTree tree(Frame,Frame->GetPowerTree(),Frame->GetTreePowerTreeID(),1);
                    tree.CreatPowerTree();
                    Request_Data(NET_PACKTYPE_MCS_REQUEST_STREAM_TREE,NULL,0);
                    break;
                }
                case NET_PACKTYPE_MCS_REQUEST_STREAM_TREE:{

                    Frame->sys_data.GetMonitorData(pzbuff+sizeof(HEAD));
                    CGreatTree tree(Frame,Frame->GetTreeCtrl1(),Frame->GetTreeMonitorTreeID(),1);
                    tree.CreatMonitorCenterTree();
                    break;
                }

            }
        }

}
