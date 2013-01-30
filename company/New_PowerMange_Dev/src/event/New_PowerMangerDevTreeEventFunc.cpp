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
***********       用户界面上的树控件       *************
*********************************************************/

/***********权限树控件勾选状态改变*****************/
void New_PowerMangerFrame::OnTreeCtrl_PowerStatusChange(wxTreeEvent& event)
{
    TREEDATA* node = ((MyTreeData *)TreeCtrl_powerManager->GetItemData(event.GetItem()))->GetData();
    if(TreeCtrl_powerManager->GetItemState(event.GetItem()) == 0){
        if(((LIMIT*)(node->data))->type == 1){   //选中的这个节点位权限组节点，旗下所有子节点相应改变状态
            TreeCtrl_powerManager->SetItemState(node->ID,1);
            wxTreeItemIdValue cookie;
            wxTreeItemId itemID = TreeCtrl_powerManager->GetFirstChild(node->ID,cookie);
            if(itemID.IsOk())
                TreeCtrl_powerManager->SetItemState(itemID,1);
            while(1){
                itemID = TreeCtrl_powerManager->GetNextChild(node->ID,cookie);
                if(itemID.IsOk())
                    TreeCtrl_powerManager->SetItemState(itemID,1);
                else
                    break;
            }
        }
        else{       //如果选取的是项目子节点，则改变子节点勾选状态，如果子节点的父节点位勾选状态，取消勾选
            TreeCtrl_powerManager->SetItemState(event.GetItem(),1);
            wxTreeItemId itemID = TreeCtrl_powerManager->GetItemParent(event.GetItem());
            TreeCtrl_powerManager->SetItemState(itemID,1);
        }
    }
    else{
        if(((LIMIT*)(node->data))->type == 1){   //选中的这个节点位权限组节点，旗下所有子节点相应改变状态
            TreeCtrl_powerManager->SetItemState(node->ID,0);
            wxTreeItemIdValue cookie;
            wxTreeItemId itemID = TreeCtrl_powerManager->GetFirstChild(node->ID,cookie);
            if(itemID.IsOk())
                TreeCtrl_powerManager->SetItemState(itemID,0);
            while(1){
                itemID = TreeCtrl_powerManager->GetNextChild(node->ID,cookie);
                if(itemID.IsOk())
                    TreeCtrl_powerManager->SetItemState(itemID,0);
                else
                    break;
            }
        }
        else{
            TreeCtrl_powerManager->SetItemState(event.GetItem(),0);
        }
   }
}

/***************用户界面上的设备专用树节点勾选状态改变*************/

void New_PowerMangerFrame::SearchAllParentItemOnItem(wxTreeItemId sid)
{
    if(sid.IsOk()){
        TREEDATA* node = ((MyTreeData *)TreeCtrl_DevTree->GetItemData(sid))->GetData();
        wxTreeItemId itemID = TreeCtrl_DevTree->GetItemParent(sid);
        if(itemID.IsOk()){
            TreeCtrl_DevTree->SetItemState(itemID,1);
            SearchAllParentItemOnItem(itemID);
        }
    }
}
void New_PowerMangerFrame::SearchAllChildItemOnItem(wxTreeItemId id,int mark)
{
    if(TreeCtrl_DevTree->ItemHasChildren(id)){
        wxTreeItemIdValue cookie;
        wxTreeItemId itemID = TreeCtrl_DevTree->GetFirstChild(id,cookie);
        if(mark == 0){
            TreeCtrl_DevTree->SetItemState(id,1);
            while(itemID.IsOk()){
                TreeCtrl_DevTree->SetItemState(itemID,1);
                SearchAllChildItemOnItem(itemID,mark);

                itemID = TreeCtrl_DevTree->GetNextChild(id,cookie);
            }
            SearchAllParentItemOnItem(id);
        }
        else{
            TreeCtrl_DevTree->SetItemState(id,0);
            while(itemID.IsOk()){
                TreeCtrl_DevTree->SetItemState(itemID,0);
                SearchAllChildItemOnItem(itemID,mark);
                itemID = TreeCtrl_DevTree->GetNextChild(id,cookie);
            }
        }
    }
    else{   //下面没有子节点
        if(mark == 0){
            TreeCtrl_DevTree->SetItemState(id,1);
            SearchAllParentItemOnItem(id);
        }
        else
            TreeCtrl_DevTree->SetItemState(id,0);
    }
}
void New_PowerMangerFrame::OnTreeCtrl_UserDevStatusChange(wxTreeEvent& event)
{
    SearchAllChildItemOnItem(event.GetItem(),TreeCtrl_DevTree->GetItemState(event.GetItem()));
}

void New_PowerMangerFrame::GetSelectionOnDevTreeOnUserGui(wxTreeItemId sid,char* power_dev,int mark)     //取得在用户界面上的树控件所多选的树节点
{
   if(TreeCtrl_DevTree->ItemHasChildren(sid)){
        wxTreeItemIdValue cookie;
        wxTreeItemId itemID = TreeCtrl_DevTree->GetFirstChild(sid,cookie);
        while(itemID.IsOk()){
            int status = TreeCtrl_DevTree->GetItemState(itemID);
            if(0 == status){
                TREEDATA* node = ((MyTreeData *)TreeCtrl_DevTree->GetItemData(itemID))->GetData();
                int ID = 0;
                switch(node->flag){
                    case TREE_FLAG_DEVICEGROUP:ID = ((DEVICE_GRP*)(node->data))->ID;break;
                    case TREE_FLAG_DEVICE:ID = ((DEVICE*)(node->data))->ID;break;
                    case TREE_FLAG_DEVICECHANNEL:ID = ((DEVICE_CHANNEL*)(node->data))->ID;break;
                    default:break;
                }
                sprintf(power_dev+strlen(power_dev),"%d,",ID);
                wxString str;
                str<<ID;
                mark = mark+str.Len()+1;
            }
            GetSelectionOnDevTreeOnUserGui(itemID,power_dev,mark);
            itemID = TreeCtrl_DevTree->GetNextChild(sid,cookie);
        }
    }
}

