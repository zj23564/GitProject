#include "../../New_PowerMangerMain.h"

#include "../../include/Tree/CGreatTree.h"

#include "../../include/define/Define_Page.h"
#include "../../include/data/Define_Data.h"
#include "../../include/define/Define.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include <wx/icon.h>
#include "../checked.xpm"
#include "../unchecked.xpm"
#include <map>
#include <wx/log.h>

extern New_PowerMangerFrame* Frame;


void New_PowerMangerFrame::Request_To_MCS(int mark,char* data,int data_len)
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
        Tcp_SendMsg(fd,buff,len);
        delete [] buff;
}

void New_PowerMangerFrame::GuiInit(void)
{
    page_count = 1;     //nodebook默认页面显出出来，计数为1

    this->SetTitle(wxT("管理服务配置客户端 HT-MS/C For HT-VAIMP V2012"));

    powerItemID.Unset();
    addCenterNodePID.Unset();
    ReadLogPic();
    SetTree();

    SetListCtrl();
    all_Device_Tree = NULL;
    Request_To_MCS(NET_PACKTYPE_MCS_REQUEST_DEVICETREE,NULL,0);

}
void New_PowerMangerFrame::ReadLogPic()
{
   // wxString log(wxT("haotel.png"));
   printf("%s  %d \n",__FILE__,__LINE__);
   // wxString log(wxT("src/Gui Function/haotel.png"));
  //  printf("%s  %s \n",__FILE__,__LINE__);
   // haotel = new wxImage(log);

}

void New_PowerMangerFrame::SetTree()
{
        wxTreeItemId tParent = TreeCtrl1->AddRoot(_("管理中心"));
        TREEDATA* m_data = new TREEDATA;
        m_data->flag = TREE_FLAG_OTHER;
        TreeCtrl1->SetItemData(tParent,(wxTreeItemData*)new MyTreeData(m_data));

        wxTreeItemId Vser = TreeCtrl1->AppendItem(tParent, _("监控中心"));
        m_data = new TREEDATA;
        m_data->flag = TREE_FLAG_MONITOR_CENTOR_NODE;
        TreeCtrl1->SetItemData(Vser,(wxTreeItemData*)new MyTreeData(m_data));
        MonitorID = Vser;

        wxTreeItemId TreeDevice = TreeCtrl1->AppendItem(tParent, _("设备节点"));
        tree_devID = TreeDevice;
        m_data = new TREEDATA;
        m_data->flag = TREE_FLAG_DEVICE_NODE;
        TreeCtrl1->SetItemData(TreeDevice,(wxTreeItemData*)new MyTreeData(m_data));

        wxTreeItemId User = TreeCtrl1->AppendItem(tParent, _("用户"));
        tree_userID = User;
        m_data = new TREEDATA;
        m_data->flag = TREE_FLAG_USER_NODE;
        TreeCtrl1->SetItemData(User,(wxTreeItemData*)new MyTreeData(m_data));

        printf("Set main tree OK\n");
        printf("Set User Device Tree start\n");
        wxTreeItemId dRoot = TreeCtrl_DevTree->AddRoot(_("当前设备节点"));
        tree_userPageDevID = dRoot;
        m_data = new TREEDATA;
        m_data->flag = TREE_FLAG_DEVICE_NODE;
        TreeCtrl_DevTree->SetItemData(dRoot,(wxTreeItemData*)new MyTreeData(m_data));

        wxTreeItemId userRoot = TreeCtrl_User->AddRoot(_("当前用户节点"));
        tree_devPageUserID = userRoot;
        m_data = new TREEDATA;
        m_data->flag = TREE_FLAG_USER_NODE;
        TreeCtrl_DevTree->SetItemData(userRoot,(wxTreeItemData*)new MyTreeData(m_data));

}
void New_PowerMangerFrame::SetTreeCtrl_powerManager()
{
    wxImageList * list = new wxImageList(5, 5, true);
    wxTreeItemId tParent = TreeCtrl_powerManager->AddRoot(_("权限项目管理树"));
    TreeCtrl_powerManager->SetItemImage(tParent,0,wxTreeItemIcon_Normal);
    powerTreeID = tParent;

}

void New_PowerMangerFrame::SetListCtrl()
{
    int i;
    wxListItem item;
    wxString str5[2] = {wxT("通道名字"), wxT("状态")};
    for(i = 0; i < 2; i++)
    {
        item.SetText(str5[i]);
        wxString st=item.GetText();
        ListCtrl_Channel->SetColumn(i,item);
        ListCtrl_Channel->InsertColumn(i,item);
        ListCtrl_Channel->SetColumnWidth(i,90);
    }
}

void New_PowerMangerFrame::Clear_DevGui()
{
    TextCtrl_DevName->Clear();
    TextCtrl_devNum->Clear();
    TextCtrl_devModel->Clear();
    TextCtrl_devIP->Clear();
    TextCtrl_devPort->Clear();
    Choice_devType->Select(wxNOT_FOUND);
    ClearOnTreeCtrl_DevUserStatus();
    ListCtrl_Channel->DeleteAllItems();
}

void New_PowerMangerFrame::Enable_DevGui()
{
    TextCtrl_devModel->Enable();
    ListCtrl_Channel->Enable();
    TextCtrl_devPort->Enable();
    TextCtrl_DevName->Enable();
    TextCtrl_devIP->Enable();
    TextCtrl_devNum->Enable();
    Choice_devType->Enable();
    Button_Sure_Add_Device->Enable();
    Button_CancelAdd_Dev->Enable();
}
void New_PowerMangerFrame::Disable_DevGui()
{
    TextCtrl_devModel->Disable();
    ListCtrl_Channel->Disable();
    TextCtrl_devPort->Disable();
    TextCtrl_DevName->Disable();
    TextCtrl_devIP->Disable();
    TextCtrl_devNum->Disable();
    Choice_devType->Disable();
    Button_Sure_Add_Device->Disable();
    Button_CancelAdd_Dev->Disable();
}


void New_PowerMangerFrame::SetUserDevTreeStatus(wxTreeItemId sid,int mark =1)
{
    if(TreeCtrl_DevTree->ItemHasChildren(sid)){
        wxTreeItemIdValue cookie;
        wxTreeItemId itemID = TreeCtrl_DevTree->GetFirstChild(sid,cookie);
        while(itemID.IsOk()){
            TreeCtrl_DevTree->SetItemState(itemID,1);
            SetUserDevTreeStatus(itemID,1);
            itemID = TreeCtrl_DevTree->GetNextChild(sid,cookie);
        }
    }
}
void New_PowerMangerFrame::Clear_UserGui()        //清除用户界面上的信息
{
    TextCtrl_UserName->Clear();
    TextCtrl_UserPwd->Clear();
    TextCtrl_UserSurePwd->Clear();
/***************清空权限树控件上的勾选项******************/
    map<int,TREEDATA*>::iterator ite;
    for(ite = sys_data.tree_limitMap.begin();ite!=sys_data.tree_limitMap.end();ite++){
        TREEDATA* power = ite->second;
        TreeCtrl_powerManager->SetItemState(power->ID,1);
    }
/***********************************************************/
/***************清空用户设备树控件上的勾选项******************/
    wxTreeItemId root = TreeCtrl_DevTree->GetRootItem();
    SetUserDevTreeStatus(root,1);
/***********************************************************/
}
void New_PowerMangerFrame::Enable_UserGui()
{
    TextCtrl_UserName->Enable();
    TextCtrl_UserPwd->Enable();
    TextCtrl_UserSurePwd->Enable();
    Button_SureUser->Enable();
    Button_CancelUser->Enable();

}
void New_PowerMangerFrame::Disable_UserGui()
{
    TextCtrl_UserName->Disable();
    TextCtrl_UserPwd->Disable();
    TextCtrl_UserSurePwd->Disable();
    Button_SureUser->Disable();
    Button_CancelUser->Disable();
}


