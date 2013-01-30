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


/*****************显示公司Log图片*********************************/
void New_PowerMangerFrame::OnPanel1Paint_Show_Log(wxPaintEvent& event)
{
    wxPaintDC tmp(Panel1);
    wxClientDC client(Panel1);
    if(haotel != NULL){
        wxBitmap bitmap = wxBitmap(*haotel);

        int x,y;
        client.GetSize(&x,&y);
        int img_x = haotel->GetWidth();
        int img_y = haotel->GetHeight();

        client.SetUserScale((double)x/img_x,(double)y/img_y);
        client.DrawBitmap(bitmap,0,0);
    }
}

void New_PowerMangerFrame::OnPanel1Resize_Refresh_Panel1(wxSizeEvent& event)
{
    Panel1->Refresh();
}
/*******************end**********************************************************/





void New_PowerMangerFrame::OnButton_SureUserClick(wxCommandEvent& event)
{

    if(1 == flag_operator_user){
        printf("add new user\n");
        AddNewUser();
    }

    else if(2 == flag_operator_user){
        printf("modify user\n");
        ModifyUserFunc();
    }



}


/******************************设备*****************************************/

void New_PowerMangerFrame::OnButton_Add_DeviceClick(wxCommandEvent& event)      //增加设备     按钮按下
{

    if(1 == flag_operator_dev)
        AddNewDev_Func();
    else if(2 == flag_operator_dev)
        ModifyDev_Func();

}

void New_PowerMangerFrame::OnChoice_devTypeSelect(wxCommandEvent& event)
{
    printf("sel num is %d\n",event.GetSelection());
    switch(event.GetSelection()){

        case 0:     //选中海康
        {
            Set_ChannelList(4); //4个通道
            break;
        }
        case 1:     //选中捷高
        {
            break;
        }
        case 2:     //选中汉邦
        {
            Set_ChannelList(16); //4个通道
            break;
        }
        case 8:     //烟感设备
        {
            Set_ChannelList(1);
            break;
        }
        case 9:     //LED
        {
            Set_ChannelList(1);
            break;
        }
        case 10:        //报警灯
        {
            Set_ChannelList(1);
            break;
        }
        default:
            break;
    }
}



/*************************编辑通道名字********************************/
void New_PowerMangerFrame::OnListCtrl_ChannelBeginLabelEdit(wxListEvent& event)
{
    ListCtrl_Channel->EndEditLabel(true);
    event.Veto();
}

void New_PowerMangerFrame::OnListCtrl_ChannelEndLabelEdit(wxListEvent& event)
{
    AddChannelDialog chnDig(0);
    if(chnDig.ShowModal()){
        wxListItem item;
        item.m_itemId = event.m_itemIndex;
        item.m_mask = wxLIST_MASK_TEXT;
        item.m_col = 0;
        item.m_text = chnDig.GetName();
        ListCtrl_Channel->SetItem(item);
        }
        DEVICE_CHANNEL* chn = new DEVICE_CHANNEL;
        memcpy(chn->name,(const char*)chnDig.GetName().mb_str(),strlen((const char*)chnDig.GetName().mb_str()));
       // chn_vect.push_back(chn);

    chnDig.Destroy();
}


void New_PowerMangerFrame::OnButton_Update_DeviceInfoClick(wxCommandEvent& event)       //提交设备信息
{


}


/*****************权限项目管理树的相关事件操作***********************************************/

void New_PowerMangerFrame::OnButton_AddPowerItemClick(wxCommandEvent& event)        //增加权限项目
{
    powerItemID = TreeCtrl_powerManager->GetSelection();
    if(powerItemID.IsOk()){
        printf("powerItemID.Unset(); is not OK\n");
        wxTreeItemId temp = TreeCtrl_powerManager->AppendItem(powerItemID, _("请输入名称"));
        TreeCtrl_powerManager->EditLabel(temp);
        TreeCtrl_powerManager->SetItemState(temp,1);
        powerItemID.Unset();
    }

}

void New_PowerMangerFrame::OnButton_ChangePowerItemClick(wxCommandEvent& event)     //修改权限项目
{


}

void New_PowerMangerFrame::OnButton_DelPowerItemClick(wxCommandEvent& event)        //删除权限项目
{

}




