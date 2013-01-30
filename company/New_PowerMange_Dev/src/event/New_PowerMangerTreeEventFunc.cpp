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


/********************************************************
***********       主树控件       ***********************
*********************************************************/
void New_PowerMangerFrame::OnTreeCtrl1SelectionChanged_DisPlay_GUI(wxTreeEvent& event)
{
    printf("tree 1 select\n");
    TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(event.GetItem()))->GetData();
    printf("node type is %x\n",node->flag);
    switch(node->flag){
        case TREE_FLAG_USER:{
            printf("user node\n");
            Page_AddUser();
            Show_UserInfo((USERINFO*)(node->data));    //显示用户信息
            break;
        }
        case TREE_FLAG_USERGROUP:{
            printf("user grp node\n");
            break;
        }
        case TREE_FLAG_DEVICE:{
            printf("device node\n");
            Page_AddDeviceNode();
            Show_DeviceInfo((DEVICE*)(node->data),(node->ID));
            break;
        }
        case TREE_FLAG_DEVICEGROUP:{
            printf("device grp node\n");
            break;
        }
        case TREE_FLAG_POWERMANAGER:{

            break;
        }
        case TREE_FLAG_OTHER:{
            printf("other node\n");
            break;
        }
    }
}

void New_PowerMangerFrame::OnTreeCtrl1ItemRightClick(wxTreeEvent& event)
{
    printf("right key down\n");

    //右键点击在用户节点上出现的菜单
    wxMenu * new_user_menu = new wxMenu();
    new_user_menu->Append(ID_NEWUSER,wxT("新建用户") );
    new_user_menu->Append(ID_NEWUSER_GROUP,wxT("新建用户组") );
    new_user_menu->Enable(ID_NEWUSER_GROUP,false);
    new_user_menu->Append(ID_MODIFYUSER,wxT("修改用户") );
    new_user_menu->Append(ID_DELUSER,wxT("删除用户") );


    //右键点击在设备组节点上出现的菜单
     wxMenu * new_devgrp_menu = new wxMenu();
     new_devgrp_menu->Append(ID_NEWDEV,wxT("增加设备节点"));
     new_devgrp_menu->Append(ID_NEWDEVGRP,wxT("增加组节点"));
     new_devgrp_menu->Append(ID_NEWDEVCHILDGRP,wxT("增加组子节点"));
     new_devgrp_menu->Append(ID_DELDEVGRP,wxT("删除组节点"));
    //右键点击设备节点上出现的菜单
     wxMenu * new_dev_menu = new wxMenu();
     new_dev_menu->Append(ID_NEWDEV,wxT("增加设备节点"));
     new_dev_menu->Append(ID_MODIFYDEV,wxT("修改设备节点"));
     new_dev_menu->Append(ID_DELDEV,wxT("删除设备节点"));
    //
      wxMenu * mon_center = new wxMenu();       //增加监控中心节点
      mon_center->Append(ID_NEWCENTER,wxT("增加监控节点"));
      mon_center->Append(ID_DELCENTER,wxT("删除监控中心"));
    //右键点击在设备根节点上出现的菜单
    wxMenu * new_devgrp_clickRoot = new wxMenu();
    new_devgrp_clickRoot->Append(ID_NEWDEVGRP,wxT("增加组节点"));

    //右键点击在用户根节点上出现的菜单
    wxMenu * new_user_clickRoot = new wxMenu();
    new_user_clickRoot->Append(ID_NEWUSER,wxT("新建用户") );
    new_user_clickRoot->Append(ID_NEWUSER_GROUP,wxT("新建用户组") );

    addCenterNodePID  = event.GetItem();

    TreeCtrl1->SelectItem(addCenterNodePID,true);

    TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(event.GetItem()))->GetData();
    switch(node->flag){
        case TREE_FLAG_USER:{
            printf("用户节点\n");
            PopupMenu ( new_user_menu , event .GetPoint());
            break;
        }
        case TREE_FLAG_USERGROUP:{
            printf("用户组节点\n");
            PopupMenu ( new_user_menu , event .GetPoint());
            break;
        }
        case TREE_FLAG_DEVICE:{
            printf("增加设备节点\n");
            new_dev_trance = node;
            add_dev_flag = TREE_FLAG_ADDDEV_AT_DEV;

            PopupMenu(new_dev_menu,event.GetPoint());
            break;
        }
        case TREE_FLAG_DEVICEGROUP:
        {
            printf("增加设备组节点\n");
            new_dev_trance = node;          //新增节点和删除节点有用(当前点击的节点信息)
            add_dev_flag = TREE_FLAG_ADDDEV_AT_GRP;

            PopupMenu(new_devgrp_menu,event.GetPoint());

            break;
        }
        case TREE_FLAG_MONITOR_CENTOR:{     //监控中心根节点
            PopupMenu(mon_center,event.GetPoint());
            break;
        }
        case TREE_FLAG_MONITOR_CENTOR_NODE:{     //监控中心根节点
            PopupMenu(mon_center,event.GetPoint());
            break;
        }
        case TREE_FLAG_USER_NODE:{      //用户的根节点
            PopupMenu(new_user_clickRoot,event.GetPoint());
            break;
        }
        case TREE_FLAG_DEVICE_NODE:{      //设备节点的根节点
            PopupMenu(new_devgrp_clickRoot,event.GetPoint());
            break;
        }
        case TREE_FLAG_OTHER:{
            printf("其它节点\n");
            break;
        }
    }
}


void New_PowerMangerFrame::OnTreeCtrl1BeginLabelEdit(wxTreeEvent& event)
{
    if(flag_edit_label != 1)
        event.Veto();
}

void New_PowerMangerFrame::OnTreeCtrl1EndLabelEdit(wxTreeEvent& event)  //结束编辑节点名字事件
{
//    if((flag_edit_label !=0)&&(flag_edit_label !=1))   //小于0 时 是鼠标双击触发的编辑事件
//        return;
    TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(event.GetItem()))->GetData();
    DEVICE_GRP* new_grp = (DEVICE_GRP*)(node->data);
    int ret = wxMessageBox(wxT("是否确定节点名字"),wxT("确认提示"),wxYES_NO);
    if(ret == wxNO){
        printf("取消名字更改\n");
        if(flag_edit_label){
            TreeCtrl1->Delete(node->ID);
            delete new_grp;
            delete node;
        }
        else{
            wxString str(new_grp->name,wxConvUTF8);
            TreeCtrl1->SetItemText(event.GetItem(),str);
        }
    }
    else if(ret == wxYES){
        printf("确认名称\n");
        wxString str = event.GetLabel();
        wxMessageBox(str);
        memcpy(new_grp->name,event.GetLabel().mb_str().data(),64);

        printf("new_grp.name >>>>>>> %s\n",new_grp->name);
        Ecode_Conv conv;
        string t_str;
        conv.GB2312ToUTF_8(t_str,new_grp->name,sizeof(DEVICE_GRP));
        memset(new_grp->name,0,64);
        memcpy(new_grp->name,(char*)t_str.c_str(),strlen((char*)t_str.c_str()));
        if(flag_edit_label){    //新增节点
            Request_To_MCS(NET_PACKTYPE_MCS_ADDDEVGRP,(char*)new_grp,sizeof(DEVICE_GRP));
            TreeCtrl1->Delete(node->ID);
        }
        else{   //修改节点
            printf("modify name is %s\n",new_grp->name);
            Request_To_MCS(NET_PACKTYPE_MCS_MODIFYGRP,(char*)new_grp,sizeof(DEVICE_GRP));
        }

    }
    flag_edit_label = false;
}





