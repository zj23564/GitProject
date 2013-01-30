/***************************************************************
 * Name:      New_PowerMangerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    zj ()
 * Created:   2012-07-13
 * Copyright: zj ()
 * License:
 **************************************************************/

#include "New_PowerMangerMain.h"
#include <wx/msgdlg.h>
#include <wx/dcclient.h>

#include "include/net/HT_NET_Engine.h"
#include "include/define/Define.h"
#include "include/define/Define_Page.h"
#include "include/Tree/CGreatTree.h"
#include <wx/log.h>
#include "include/GlobalFunc.h"
//(*InternalHeaders(New_PowerMangerFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <windows.h>


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(New_PowerMangerFrame)
const long New_PowerMangerFrame::ID_TREECTRL1 = wxNewId();
const long New_PowerMangerFrame::ID_PANEL1 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT7 = wxNewId();
const long New_PowerMangerFrame::ID_TEXTCTRL3 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT8 = wxNewId();
const long New_PowerMangerFrame::ID_TEXTCTRL4 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT9 = wxNewId();
const long New_PowerMangerFrame::ID_TEXTCTRL5 = wxNewId();
const long New_PowerMangerFrame::ID_BUTTON9 = wxNewId();
const long New_PowerMangerFrame::ID_BUTTON10 = wxNewId();
const long New_PowerMangerFrame::ID_BUTTON12 = wxNewId();
const long New_PowerMangerFrame::ID_TREECTRL4 = wxNewId();
const long New_PowerMangerFrame::ID_BUTTON1 = wxNewId();
const long New_PowerMangerFrame::ID_BUTTON2 = wxNewId();
const long New_PowerMangerFrame::ID_TREECTRL2 = wxNewId();
const long New_PowerMangerFrame::ID_PANEL3 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT1 = wxNewId();
const long New_PowerMangerFrame::ID_TEXTCTRL1 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT2 = wxNewId();
const long New_PowerMangerFrame::ID_TEXTCTRL2 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT3 = wxNewId();
const long New_PowerMangerFrame::ID_CHOICE1 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT4 = wxNewId();
const long New_PowerMangerFrame::ID_TEXTCTRL7 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT5 = wxNewId();
const long New_PowerMangerFrame::ID_TEXTCTRL8 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT6 = wxNewId();
const long New_PowerMangerFrame::ID_TEXTCTRL9 = wxNewId();
const long New_PowerMangerFrame::ID_STATICTEXT11 = wxNewId();
const long New_PowerMangerFrame::ID_LISTCTRL5 = wxNewId();
const long New_PowerMangerFrame::ID_BUTTON5 = wxNewId();
const long New_PowerMangerFrame::ID_BUTTON6 = wxNewId();
const long New_PowerMangerFrame::ID_TREECTRL3 = wxNewId();
const long New_PowerMangerFrame::ID_PANEL8 = wxNewId();
const long New_PowerMangerFrame::ID_NOTEBOOK1 = wxNewId();
const long New_PowerMangerFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long New_PowerMangerFrame::ID_NEWUSER = wxNewId();
const long New_PowerMangerFrame::ID_MODIFYUSER = wxNewId();
const long New_PowerMangerFrame::ID_NEWUSER_GROUP = wxNewId();
const long New_PowerMangerFrame::ID_DELUSER = wxNewId();
const long New_PowerMangerFrame::ID_NEWDEV = wxNewId();
const long New_PowerMangerFrame::ID_MODIFYDEV = wxNewId();
const long New_PowerMangerFrame::ID_DELDEV = wxNewId();
const long New_PowerMangerFrame::ID_NEWDEVGRP = wxNewId();
const long New_PowerMangerFrame::ID_NEWDEVCHILDGRP = wxNewId();
const long New_PowerMangerFrame::ID_SUREADDDEVGRP = wxNewId();
const long New_PowerMangerFrame::ID_DELDEVGRP = wxNewId();

const long New_PowerMangerFrame::ID_NEWCENTER = wxNewId();
const long New_PowerMangerFrame::ID_DELCENTER = wxNewId();


int New_PowerMangerFrame::session;

BEGIN_EVENT_TABLE(New_PowerMangerFrame,wxFrame)
    //(*EventTable(New_PowerMangerFrame)
    //*)
END_EVENT_TABLE()

New_PowerMangerFrame::New_PowerMangerFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(New_PowerMangerFrame)
    wxBoxSizer* BoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer29;
    wxBoxSizer* BoxSizer51;
    wxBoxSizer* BoxSizer21;
    wxBoxSizer* BoxSizer13;
    wxBoxSizer* BoxSizer41;
    wxBoxSizer* BoxSizer37;
    wxBoxSizer* BoxSizer48;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer16;
    wxBoxSizer* BoxSizer44;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer45;
    wxBoxSizer* BoxSizer14;
    wxGridSizer* GridSizer1;
    wxBoxSizer* BoxSizer17;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer55;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, _("浩特视频应用综合管理平台 HT-VAIMP V2012"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    TreeCtrl1 = new wxTreeCtrl(this, ID_TREECTRL1, wxDefaultPosition, wxSize(215,616), wxTR_EDIT_LABELS|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
    BoxSizer2->Add(TreeCtrl1, 6, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer13 = new wxBoxSizer(wxVERTICAL);
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    StaticText7 = new wxStaticText(Panel3, ID_STATICTEXT7, _("用户名"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT7"));
    BoxSizer14->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_UserName = new wxTextCtrl(Panel3, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    TextCtrl_UserName->Disable();
    BoxSizer14->Add(TextCtrl_UserName, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(Panel3, ID_STATICTEXT8, _("密码"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT8"));
    BoxSizer14->Add(StaticText8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_UserPwd = new wxTextCtrl(Panel3, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    TextCtrl_UserPwd->Disable();
    BoxSizer14->Add(TextCtrl_UserPwd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(Panel3, ID_STATICTEXT9, _("确认密码"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT9"));
    BoxSizer14->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_UserSurePwd = new wxTextCtrl(Panel3, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    TextCtrl_UserSurePwd->Disable();
    BoxSizer14->Add(TextCtrl_UserSurePwd, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer13->Add(BoxSizer14, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, Panel3, _("权限设置"));
    BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer2->Add(BoxSizer16, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer48 = new wxBoxSizer(wxVERTICAL);
    Button_AddPowerItem = new wxButton(Panel3, ID_BUTTON9, _("增加权限项目"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    BoxSizer48->Add(Button_AddPowerItem, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_ChangePowerItem = new wxButton(Panel3, ID_BUTTON10, _("修改权限项目"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    BoxSizer48->Add(Button_ChangePowerItem, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_DelPowerItem = new wxButton(Panel3, ID_BUTTON12, _("删除权限项目"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    BoxSizer48->Add(Button_DelPowerItem, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer17->Add(BoxSizer48, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer55 = new wxBoxSizer(wxHORIZONTAL);
    TreeCtrl_powerManager = new wxTreeCtrl(Panel3, ID_TREECTRL4, wxDefaultPosition, wxDefaultSize, wxTR_EDIT_LABELS|wxTR_HIDE_ROOT|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL4"));
    BoxSizer55->Add(TreeCtrl_powerManager, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer17->Add(BoxSizer55, 4, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer17, 8, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer21 = new wxBoxSizer(wxHORIZONTAL);
    Button_SureUser = new wxButton(Panel3, ID_BUTTON1, _("确认"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer21->Add(Button_SureUser, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_CancelUser = new wxButton(Panel3, ID_BUTTON2, _("取消"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer21->Add(Button_CancelUser, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer21, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer13->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer12->Add(BoxSizer13, 3, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    TreeCtrl_DevTree = new wxTreeCtrl(Panel3, ID_TREECTRL2, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL2"));
    BoxSizer6->Add(TreeCtrl_DevTree, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer12->Add(BoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(BoxSizer12);
    BoxSizer12->Fit(Panel3);
    BoxSizer12->SetSizeHints(Panel3);
    Panel8 = new wxPanel(Notebook1, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    BoxSizer29 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer37 = new wxBoxSizer(wxVERTICAL);
    BoxSizer44 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer1 = new wxGridSizer(0, 4, 0, 0);
    StaticText1 = new wxStaticText(Panel8, ID_STATICTEXT1, _("名字"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    GridSizer1->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_DevName = new wxTextCtrl(Panel8, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl_DevName->Disable();
    GridSizer1->Add(TextCtrl_DevName, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel8, ID_STATICTEXT2, _("设备统一编号"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    GridSizer1->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_devNum = new wxTextCtrl(Panel8, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    TextCtrl_devNum->Disable();
    GridSizer1->Add(TextCtrl_devNum, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel8, ID_STATICTEXT3, _("选择设备厂家"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    GridSizer1->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice_devType = new wxChoice(Panel8, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice_devType->Append(_("海康"));
    Choice_devType->Append(_("冠辉"));
    Choice_devType->Append(_("汉邦"));
    Choice_devType->Append(_("大华"));
    Choice_devType->Append(_("捷高"));
    Choice_devType->Append(_("微蒂"));
    Choice_devType->Append(_("德加拉"));
    Choice_devType->Append(_("网力"));
    Choice_devType->Append(_("烟感设备"));
    Choice_devType->Append(_("LED"));
    Choice_devType->Append(_("报警灯"));
    Choice_devType->Disable();
    GridSizer1->Add(Choice_devType, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(Panel8, ID_STATICTEXT4, _("设备型号"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    GridSizer1->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_devModel = new wxTextCtrl(Panel8, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    TextCtrl_devModel->Disable();
    GridSizer1->Add(TextCtrl_devModel, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(Panel8, ID_STATICTEXT5, _("设备ＩＰ"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    GridSizer1->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_devIP = new wxTextCtrl(Panel8, ID_TEXTCTRL8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    TextCtrl_devIP->Disable();
    GridSizer1->Add(TextCtrl_devIP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(Panel8, ID_STATICTEXT6, _("设备端口"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    GridSizer1->Add(StaticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl_devPort = new wxTextCtrl(Panel8, ID_TEXTCTRL9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
    TextCtrl_devPort->Disable();
    GridSizer1->Add(TextCtrl_devPort, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer44->Add(GridSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer37->Add(BoxSizer44, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText11 = new wxStaticText(Panel8, ID_STATICTEXT11, _("请在下面通道属性表中输入该设备的通道相关参数"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    BoxSizer4->Add(StaticText11, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer37->Add(BoxSizer4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer45 = new wxBoxSizer(wxHORIZONTAL);
    ListCtrl_Channel = new wxListCtrl(Panel8, ID_LISTCTRL5, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_EDIT_LABELS, wxDefaultValidator, _T("ID_LISTCTRL5"));
    BoxSizer45->Add(ListCtrl_Channel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer37->Add(BoxSizer45, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer51 = new wxBoxSizer(wxHORIZONTAL);
    Button_Sure_Add_Device = new wxButton(Panel8, ID_BUTTON5, _("确认"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer51->Add(Button_Sure_Add_Device, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_CancelAdd_Dev = new wxButton(Panel8, ID_BUTTON6, _("取消"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer51->Add(Button_CancelAdd_Dev, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer37->Add(BoxSizer51, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer29->Add(BoxSizer37, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer41 = new wxBoxSizer(wxHORIZONTAL);
    TreeCtrl_User = new wxTreeCtrl(Panel8, ID_TREECTRL3, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL3"));
    BoxSizer41->Add(TreeCtrl_User, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer29->Add(BoxSizer41, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel8->SetSizer(BoxSizer29);
    BoxSizer29->Fit(Panel8);
    BoxSizer29->SetSizeHints(Panel8);
    Notebook1->AddPage(Panel1, _("欢迎光临"), false);
    Notebook1->AddPage(Panel3, _("用户"), false);
    Notebook1->AddPage(Panel8, _("设备信息"), false);
    BoxSizer3->Add(Notebook1, 4, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 5, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);
    Center();

    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT,(wxObjectEventFunction)&New_PowerMangerFrame::OnTreeCtrl1BeginLabelEdit);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_END_LABEL_EDIT,(wxObjectEventFunction)&New_PowerMangerFrame::OnTreeCtrl1EndLabelEdit);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&New_PowerMangerFrame::OnTreeCtrl1ItemRightClick);
    Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&New_PowerMangerFrame::OnTreeCtrl1SelectionChanged_DisPlay_GUI);
    Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&New_PowerMangerFrame::OnPanel1Paint_Show_Log,0,this);
    Panel1->Connect(wxEVT_SIZE,(wxObjectEventFunction)&New_PowerMangerFrame::OnPanel1Resize_Refresh_Panel1,0,this);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&New_PowerMangerFrame::OnButton_AddPowerItemClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&New_PowerMangerFrame::OnButton_ChangePowerItemClick);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&New_PowerMangerFrame::OnButton_DelPowerItemClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&New_PowerMangerFrame::OnButton_SureUserClick);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::OnChoice_devTypeSelect);
    Connect(ID_LISTCTRL5,wxEVT_COMMAND_LIST_BEGIN_LABEL_EDIT,(wxObjectEventFunction)&New_PowerMangerFrame::OnListCtrl_ChannelBeginLabelEdit);
    Connect(ID_LISTCTRL5,wxEVT_COMMAND_LIST_END_LABEL_EDIT,(wxObjectEventFunction)&New_PowerMangerFrame::OnListCtrl_ChannelEndLabelEdit);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&New_PowerMangerFrame::OnButton_Add_DeviceClick);
    //*)
    Connect(ID_TREECTRL4,wxEVT_COMMAND_TREE_STATE_IMAGE_CLICK,(wxObjectEventFunction)&New_PowerMangerFrame::OnTreeCtrl_PowerStatusChange);
    Connect(ID_TREECTRL2,wxEVT_COMMAND_TREE_STATE_IMAGE_CLICK,(wxObjectEventFunction)&New_PowerMangerFrame::OnTreeCtrl_UserDevStatusChange);
    Connect(ID_TREECTRL3,wxEVT_COMMAND_TREE_STATE_IMAGE_CLICK,(wxObjectEventFunction)&New_PowerMangerFrame::OnTreeCtrl_DevUserStatusChange);
    Connect(ID_NEWUSER,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::NewUser);          //新增用户
    Connect(ID_NEWUSER_GROUP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::NewUserGroup);          //新增用户
    Connect(ID_DELUSER,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::DelUser);          //删除用户
    Connect(ID_MODIFYUSER,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::ModifyUser);        //重命名用户
    Connect(ID_NEWDEV,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::NewDev);        //增加设备节点
    Connect(ID_MODIFYDEV,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::ModifyDev);        //修改设备节点
    Connect(ID_DELDEV,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::DelDev);        //删除设备节点


    Connect(ID_NEWDEVGRP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::NewDevGrp);        //增加设备组节点
    Connect(ID_NEWDEVCHILDGRP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::NewDevChildGrp);        //增加设备组节点
    Connect(ID_DELDEVGRP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::DelDevGrp);
       //删除设备分组

   Connect(ID_NEWCENTER,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::AddNewCentor);
   Connect(ID_DELCENTER,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&New_PowerMangerFrame::DelCentor);

    //NetInit();


}

New_PowerMangerFrame::~New_PowerMangerFrame()
{
    //(*Destroy(New_PowerMangerFrame)
    //*)
}

void New_PowerMangerFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void New_PowerMangerFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void New_PowerMangerFrame::NetInit()
{
    HT_NET_Engine_init(8,1000);
    printf("mcs ip is %s\n",McsIp);
    printf("mcs ip is %d\n",McsPort);

    fd = Tcp_Connect(McsIp,McsPort,ReceviedData,Event_Sys,NULL,1,0);
    if(fd == NULL){
        wxLogMessage(wxT("连接服务器失败"));
        Destroy();
    }
    else{
        SetTreeCtrl_powerManager();
        GuiInit();

    }
}



