#include "../../New_PowerMangerMain.h"
#include "../../AddCenterNodeDialog.h"
#include <wx/msgdlg.h>
#include <wx/dcclient.h>
#include "../../include/define/Define.h"
#include "../../include/define/Define_Page.h"
#include "../../include/Tree/CGreatTree.h"
#include <wx/log.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <map>
#include "../../AddChannelDialog.h"
#include "../../include/encode_conv/Ecode_Conv.h"



void New_PowerMangerFrame::AddNewCentor(wxCommandEvent& event)      //点击树右键菜单的增加监控中心事件
{
    printf("增加监控中心\n");
   // center_node = NULL;
    AddCenterNodeDialog* center = new AddCenterNodeDialog(0);
    if(center->ShowModal()){
        TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(TreeCtrl1->GetSelection()))->GetData();
        if(node->flag != TREE_FLAG_MONITOR_CENTOR_NODE)
            if(0 != ((Tree_Monitor*)(node->data))->monitor.type){
                wxLogWarning(wxT("该节点不能带有服务节点"));
                return;
            }
        MONITOR_CENTER* t_monitor = (MONITOR_CENTER*)(center->Get_Center_Node());
//        Request_To_MCS(NET_PACKTYPE_MCS_DELDEVGRP,(char*)t_monitor,sizeof(MONITOR_CENTER));
        wxString str(t_monitor->name,wxConvUTF8);
        wxTreeItemId ID = TreeCtrl1->AppendItem(addCenterNodePID,str);
        TREEDATA* m_data = new TREEDATA;
        m_data->flag = TREE_FLAG_MONITOR_CENTOR;
        m_data->data = (char*)t_monitor;
        TreeCtrl1->SetItemData(ID,(wxTreeItemData*)new MyTreeData(m_data));
    }
}

void New_PowerMangerFrame::DelCentor(wxCommandEvent& event)      //点击树右键菜单的删除监控中心事件
{
    printf("删除监控中心\n");
    TreeCtrl1->Delete(TreeCtrl1->GetSelection());

}

void New_PowerMangerFrame::NewDev(wxCommandEvent& event)    //增加设备选项事件  菜单选项选中
{
    Clear_DevGui();
    Page_AddDeviceNode();
    flag_operator_dev = 1;
}

void New_PowerMangerFrame::ModifyDev(wxCommandEvent& event)   //修改设备选项事件  菜单选项选中
{
    Clear_DevGui();
    Page_AddDeviceNode();
    TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(TreeCtrl1->GetSelection()))->GetData();
    Show_DeviceInfo((DEVICE*)(node->data),node->ID);
    Enable_DevGui();
    cancel_devUserMap.clear();
    flag_operator_dev = 2;
}
void New_PowerMangerFrame::NewDevGrp(wxCommandEvent& event)     //增加设备组节点事件
{

  DEVICE_GRP* new_grp = new DEVICE_GRP;
  memset(new_grp,0,sizeof(DEVICE_GRP));
  printf("edit new dev group name\n");
  if(NULL != new_dev_trance){   //没有点击在设备根节点上
      printf("name is %s\n",((DEVICE_GRP*)(new_dev_trance->data))->name);
      wxTreeItemId pTree = TreeCtrl1->GetItemParent(new_dev_trance->ID);

       new_grp->lev =  ((DEVICE_GRP*)(new_dev_trance->data))->lev;       //新设备节点的等级预存储
       if(new_grp->lev <= 1){            //如果增加的是最上层节点，等级定为1
            new_grp->PID = 0;
       }
       else{
            new_grp->PID =  ((DEVICE_GRP*)(new_dev_trance->data))->PID;     //如果增加的不是最高等级节点，则将等级定为和当前点击的节点同等级
       }
        printf("new devgrp pid is %d\n",new_grp->PID);
        wxTreeItemId ID = TreeCtrl1->AppendItem(pTree,wxT("请输入新组节点名称"));
        new_dev_node = new TREEDATA;
        new_dev_node->ID = ID;
        new_dev_node->flag = TREE_FLAG_DEVICEGROUP;
        new_dev_node->data = (char*)new_grp;
        TreeCtrl1->SetItemData(new_dev_node->ID,(wxTreeItemData*)new MyTreeData(new_dev_node));
        if(ID.IsOk()){
            printf("ID OK\n");
            flag_edit_label = 1;
            TreeCtrl1->EditLabel(ID);

        }
        else{
            printf("ID error\n");
        }
  }
  else{     //点击在设备根节点上
        new_grp->PID = 0;
        new_grp->lev = 1;
        wxTreeItemId ID = TreeCtrl1->AppendItem(GetTreeDeviceParentID(),wxT("请输入新组节点名称"));
        TreeCtrl1->Expand(GetTreeDeviceParentID());
        new_dev_node = new TREEDATA;
        new_dev_node->ID = ID;

        new_dev_node->flag = TREE_FLAG_DEVICEGROUP;
        new_dev_node->data = (char*)new_grp;
        TreeCtrl1->SetItemData(new_dev_node->ID,(wxTreeItemData*)new MyTreeData(new_dev_node));
        flag_edit_label = 1;
        TreeCtrl1->EditLabel(ID);

        new_dev_trance = NULL;

  }
}

void New_PowerMangerFrame::NewDevChildGrp(wxCommandEvent& event)    //增加子设备树节点事件
{
    DEVICE_GRP* new_grp = new DEVICE_GRP;
    memset(new_grp,0,sizeof(DEVICE_GRP));
    wxTreeItemId pTree = new_dev_trance->ID;
    new_grp->lev =  (((DEVICE_GRP*)(new_dev_trance->data))->lev)+1;       //新设备节点的等级预存储
    new_grp->PID =  ((DEVICE_GRP*)(new_dev_trance->data))->ID;
    wxTreeItemId ID = TreeCtrl1->AppendItem(pTree,wxT("请输入新组节点名称"));
    TreeCtrl1->Expand(pTree);
    new_dev_node = new TREEDATA;
    new_dev_node->ID = ID;
    new_dev_node->flag = TREE_FLAG_DEVICEGROUP;
    new_dev_node->data = (char*)new_grp;
    TreeCtrl1->SetItemData(ID,(wxTreeItemData*)new MyTreeData(new_dev_node));
    flag_edit_label = 1;

    TreeCtrl1->EditLabel(ID);
    new_dev_trance = NULL;
}

void New_PowerMangerFrame::DelDev(wxCommandEvent& event)
{
    int ret = wxMessageBox(wxT("确认删除该设备节点"),wxT("删除设备"),wxYES_NO);
    if(ret == wxNO){
        printf("取消增加设备节点\n");
        return ;
    }
    printf("del device node\n");
    wxTreeItemId t_select = TreeCtrl1->GetSelection();
    TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(t_select))->GetData();
    DEVICE t_dev;
    memset(&t_dev,0,sizeof(DEVICE));
    memcpy(&t_dev,node->data,sizeof(DEVICE));      //需要删除的设备节点
    printf("del dev name is %s\n",t_dev.name);
    printf("del dev ID is %d\n",t_dev.ID);
//接下来找到设备节点下的所有通道节点,只需要在界面上删除，数据库中可以根据设备节点找到旗下所有的通道节点


    wxTreeItemIdValue cookie;
    wxTreeItemId item = TreeCtrl1->GetFirstChild(t_select,cookie);
    while(item.IsOk()){
        TreeCtrl1->Delete(item);
        item = TreeCtrl1->GetFirstChild(t_select,cookie);
    }

    TreeCtrl1->Delete(t_select);

     Request_To_MCS(NET_PACKTYPE_MCS_DELETEDEVICE,(char*)&t_dev,sizeof(DEVICE));
}

void New_PowerMangerFrame::DelDevNodeFunc(wxTreeItemId ID)      //用于删除设备组的时候的递归算法
{
    wxTreeItemIdValue val;
    wxTreeItemId m_ID;
    if(TreeCtrl1->ItemHasChildren(ID) == false){

        TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(ID))->GetData();
        del_dev_grp_num.push_back(((DEVICE_GRP*)(node->data))->ID);

        return;
    }
   m_ID = TreeCtrl1->GetFirstChild(ID,val);

    while(m_ID.IsOk()){
         TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(m_ID))->GetData();
         if(node->flag == TREE_FLAG_DEVICE){
            printf("正在删除的节点是设备节点 %d\n",((DEVICE*)(node->data))->ID);

            del_dev_num.push_back(((DEVICE*)(node->data))->ID);
         }
         else if(node->flag == TREE_FLAG_DEVICEGROUP){
            printf("正在删除的节点是设备组节点  %d\n",((DEVICE_GRP*)(node->data))->ID);
            del_dev_grp_num.push_back(((DEVICE_GRP*)(node->data))->ID);
         }
            //printf("被删除的节点ID  %d\n",);
         if(TreeCtrl1->ItemHasChildren(m_ID)){
            printf("还有子节点\n");
            DelDevNodeFunc(m_ID);
         }
         m_ID = TreeCtrl1-> GetNextChild(ID,val);
    }
}

void New_PowerMangerFrame::DelDevGrp(wxCommandEvent& event)  //删除设备分组
{
    printf("删除设备分组\n");
    wxTreeItemId ID = new_dev_trance->ID;

    DelDevNodeFunc(ID);
    TreeCtrl1->DeleteChildren(ID);
    TreeCtrl1->Delete(ID);
    vector<int>::iterator ite;
    int del_dev_size = del_dev_num.size();
    int del_dev_grp_size = del_dev_grp_num.size();
    COUNT del_count;
    del_count.Count_Device = del_dev_size;
    del_count.Count_Group = del_dev_grp_size;
    char* buff = new char[sizeof(COUNT)+sizeof(int)*(del_dev_size+del_dev_grp_size)];
    memcpy(buff,&del_count,sizeof(COUNT));
    int i = 0;
    for(ite = del_dev_grp_num.begin();ite!=del_dev_grp_num.end();ite++){
        *(buff+sizeof(COUNT)+i*sizeof(int)) = *ite;
        i++;
    }
    int j = 0;
    for(ite = del_dev_num.begin();ite!=del_dev_num.end();ite++){
        *(buff+sizeof(COUNT)+i*sizeof(int)+j*sizeof(int)) = *ite;
        j++;
    }

    del_dev_num.clear();
    del_dev_grp_num.clear();
    for(int k = 0;k<i+j;k++)
        printf("del ID  is %d\n",*(buff+sizeof(COUNT)+k*sizeof(int)));


    Request_To_MCS(NET_PACKTYPE_MCS_DELDEVGRP,buff,sizeof(COUNT)+sizeof(int)*(del_dev_size+del_dev_grp_size));
    delete [] buff;
}

/******************************用户**************************************************/
void New_PowerMangerFrame::NewUser(wxCommandEvent& event)
{
    Page_AddUser();
    Clear_UserGui();
    Enable_UserGui();
    flag_operator_user = 1;
}

void New_PowerMangerFrame::ModifyUser(wxCommandEvent& event)
{
    Page_AddUser();
    Enable_UserGui();
    TextCtrl_UserName->Disable();   //用户名不能修改
    flag_operator_user = 2;
}

void New_PowerMangerFrame::DelUser(wxCommandEvent& event)
{
    DelUserFunc();
}

void New_PowerMangerFrame::NewUserGroup(wxCommandEvent& event)
{

}



