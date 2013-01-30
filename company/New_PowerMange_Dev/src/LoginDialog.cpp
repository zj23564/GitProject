#include "../include/LoginDialog.h"
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <wx/log.h>
//(*InternalHeaders(LoginDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(LoginDialog)
const long LoginDialog::ID_STATICTEXT1 = wxNewId();
const long LoginDialog::ID_TEXTCTRL1 = wxNewId();
const long LoginDialog::ID_STATICTEXT2 = wxNewId();
const long LoginDialog::ID_TEXTCTRL2 = wxNewId();
const long LoginDialog::ID_STATICTEXT3 = wxNewId();
const long LoginDialog::ID_TEXTCTRL3 = wxNewId();
const long LoginDialog::ID_STATICTEXT4 = wxNewId();
const long LoginDialog::ID_TEXTCTRL4 = wxNewId();
const long LoginDialog::ID_BUTTON1 = wxNewId();
const long LoginDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LoginDialog,wxDialog)
	//(*EventTable(LoginDialog)
	//*)
END_EVENT_TABLE()

LoginDialog::LoginDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(LoginDialog)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, _("请登录"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("用户名"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer4->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Name = new wxTextCtrl(this, ID_TEXTCTRL1, _("admin"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer4->Add(TextCtrl_Name, 3, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("密码"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer5->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Passwd = new wxTextCtrl(this, ID_TEXTCTRL2, _("123456"), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer5->Add(TextCtrl_Passwd, 3, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("服务器IP"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer6->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_IP = new wxTextCtrl(this, ID_TEXTCTRL3, _("192.168.1.86"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer6->Add(TextCtrl_IP, 3, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("服务端口"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer7->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Port = new wxTextCtrl(this, ID_TEXTCTRL4, _("3250"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	BoxSizer7->Add(TextCtrl_Port, 3, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
	Button_Login = new wxButton(this, ID_BUTTON1, _("登录"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer8->Add(Button_Login, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button_cancel = new wxButton(this, ID_BUTTON2, _("取消"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer8->Add(Button_cancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 6, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LoginDialog::OnButton_LoginClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LoginDialog::OnButton_cancelClick);
	//*)
	GuiInit();
}

LoginDialog::~LoginDialog()
{
	//(*Destroy(LoginDialog)
	//*)
}
void LoginDialog::GuiInit()
{
//    TextCtrl_Name->Clear();
//    TextCtrl_Passwd->Clear();
//    TextCtrl_IP->Clear();
//    TextCtrl_Port->Clear();
}
int LoginDialog::Open_ConfigFile(const char* name,const char* passwd)
{
    FILE * fp;
    char buff[255];
    fp = fopen("admin.txt", "r");
    if (NULL == fp)
    {
        return 0;
    }
    fgets(buff,255,fp);

    if(strncmp(name,buff,strlen(buff)-1) == 0){

        printf("name right\n");
    }
    else{
       printf("name error\n");
       return 1;    //没有这个用户
    }

    memset(buff,0,255);
    fgets(buff,255,fp);

    if(strncmp(passwd,buff,strlen(buff)-1) == 0){
        printf("passwd right\n");
    }
    else{
        printf("passwd error\n");
        return 2;       //密码错误
    }
    fclose(fp);
    return 0;   //登录成功

}
void LoginDialog::OnButton_LoginClick(wxCommandEvent& event)    //登录
{
    if(TextCtrl_Name->GetValue().IsEmpty()){
        wxLogWarning(wxT("请输入名字"));
        return;
    }
    if(TextCtrl_Passwd->GetValue().IsEmpty()){
        wxLogWarning(wxT("请输入密码"));
        return;
    }
    if(TextCtrl_IP->GetValue().IsEmpty()){
        wxLogWarning(wxT("请输入服务器IP地址"));
        return;
    }
    if(TextCtrl_Port->GetValue().IsEmpty()){
        wxLogWarning(wxT("请输入服务端口"));
        return;
    }
    memcpy(serverIP,(const char*)TextCtrl_IP->GetValue().mb_str(),16);
    serverPort = wxAtoi(TextCtrl_Port->GetValue());
    printf("serverIP ip is %s\n",serverIP);
    printf("serverPort ip is %d\n",serverPort);
    int ret = Open_ConfigFile((const char*)TextCtrl_Name->GetValue().mb_str(),(const char*)TextCtrl_Passwd->GetValue().mb_str());
    switch(ret){

        case 0:
//            memcpy(serverIP,(const char*)TextCtrl_Name->GetValue().mb_str(),16);
//            serverPort = wxAtoi(TextCtrl_Port->GetValue());
            break;
        case 1:
            wxLogWarning(wxT("no such user"));
            return;
        case 2:
            wxLogWarning(wxT("passwd error"));
            return;
        default:
            break;
    }

    EndModal(1);
}

void LoginDialog::OnButton_cancelClick(wxCommandEvent& event)   //取消登录
{
    EndModal(0);
}
