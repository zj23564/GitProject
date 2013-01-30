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

void New_PowerMangerFrame::ClearOnTreeCtrl_DevUserStatus()
{
    wxTreeItemId root = TreeCtrl_User->GetRootItem();
    wxTreeItemIdValue cookie;
    wxTreeItemId itemID = TreeCtrl_User->GetFirstChild(root,cookie);
    while(itemID.IsOk()){
        TreeCtrl_User->SetItemState(itemID,1);
        itemID = TreeCtrl_User->GetNextChild(root,cookie);
    }
}

void New_PowerMangerFrame::OnTreeCtrl_DevUserStatusChange(wxTreeEvent& event)
{
    printf("user tree status\n");
    if(0 == TreeCtrl_User->GetItemState(event.GetItem())){
        TreeCtrl_User->SetItemState(event.GetItem(),1);
        TREEDATA* node = ((MyTreeData *)TreeCtrl_User->GetItemData(event.GetItem()))->GetData();
        USERINFO* usr= (USERINFO*)(node->data);
        cancel_devUserMap[usr->ID] = usr;
    }
    else{
        TreeCtrl_User->SetItemState(event.GetItem(),0);
    }
}

void New_PowerMangerFrame::GetSelectionOnUserTreeOnDevGuiDevUserStatus(DEVBELONGUSER* belong)
{
    wxTreeItemId root = TreeCtrl_User->GetRootItem();
    wxTreeItemIdValue cookie;
    wxTreeItemId itemID = TreeCtrl_User->GetFirstChild(root,cookie);
    printf("error here?\n");
    while(itemID.IsOk()){
        if(0 == TreeCtrl_User->GetItemState(itemID)){
            TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(itemID))->GetData();
            memcpy(belong->usr[belong->num],((USERINFO*)(node->data))->Name,16);
            belong->num++;
            printf("or here\n");
        }
        itemID = TreeCtrl_User->GetNextChild(root,cookie);
    }
}


