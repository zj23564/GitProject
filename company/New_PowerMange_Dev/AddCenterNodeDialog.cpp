#include "AddCenterNodeDialog.h"
#include "New_PowerMangerMain.h"
#include "include/data/Define_Data.h"
#include "include/define/Define_Page.h"
#include "include/encode_conv/Ecode_Conv.h"
#include <wx/log.h>
//(*InternalHeaders(AddCenterNodeDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
extern New_PowerMangerFrame* Frame;
//(*IdInit(AddCenterNodeDialog)
const long AddCenterNodeDialog::ID_STATICTEXT1 = wxNewId();
const long AddCenterNodeDialog::ID_TEXTCTRL1 = wxNewId();
const long AddCenterNodeDialog::ID_STATICTEXT2 = wxNewId();
const long AddCenterNodeDialog::ID_CHOICE1 = wxNewId();
const long AddCenterNodeDialog::ID_STATICTEXT3 = wxNewId();
const long AddCenterNodeDialog::ID_TEXTCTRL2 = wxNewId();
const long AddCenterNodeDialog::ID_STATICTEXT4 = wxNewId();
const long AddCenterNodeDialog::ID_TEXTCTRL3 = wxNewId();
const long AddCenterNodeDialog::ID_BUTTON1 = wxNewId();
const long AddCenterNodeDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AddCenterNodeDialog,wxDialog)
	//(*EventTable(AddCenterNodeDialog)
	//*)
END_EVENT_TABLE()

AddCenterNodeDialog::AddCenterNodeDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AddCenterNodeDialog)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("名字"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_CenterName = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(TextCtrl_CenterName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("类型"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer2->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Choice_CenterType = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice_CenterType->Append(_("监控中心"));
	Choice_CenterType->Append(_("管理服务"));
	Choice_CenterType->Append(_("流媒体服务"));
	Choice_CenterType->Append(_("日志服务"));
	Choice_CenterType->Append(_("报警服务"));
	Choice_CenterType->Append(_("存储服务"));
	BoxSizer2->Add(Choice_CenterType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("IP"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_CenterIP = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer4->Add(TextCtrl_CenterIP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("端口"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer4->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_CenterPort = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer4->Add(TextCtrl_CenterPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer5->Add(BoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button_CenterSuer = new wxButton(this, ID_BUTTON1, _("确认"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer5->Add(Button_CenterSuer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button_CenterCancel = new wxButton(this, ID_BUTTON2, _("取消"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer5->Add(Button_CenterCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer5->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AddCenterNodeDialog::OnButton_CenterSuerClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AddCenterNodeDialog::OnButton_CenterCancelClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&AddCenterNodeDialog::OnClose);
	//*)

	CenterNodeDialogInit();
}

AddCenterNodeDialog::~AddCenterNodeDialog()
{
	//(*Destroy(AddCenterNodeDialog)
	//*)
}

void AddCenterNodeDialog::CenterNodeDialogInit()
{
    TextCtrl_CenterName->Clear();;
    TextCtrl_CenterPort->Clear();
    TextCtrl_CenterIP->Clear();
}

void AddCenterNodeDialog::OnButton_CenterSuerClick(wxCommandEvent& event)       //确认监控中心节点
{
     if(TextCtrl_CenterName->GetValue().IsEmpty()){
        wxLogWarning(wxT("请输入名字"));
        return;
    }
    if(TextCtrl_CenterIP->GetValue().IsEmpty()){
        wxLogWarning(wxT("请输入ip"));
        return;
    }
    if(TextCtrl_CenterPort->GetValue().IsEmpty()){
        wxLogWarning(wxT("请输入端口"));
        return;
    }

    if(Choice_CenterType->GetSelection() == -1){
        wxLogWarning(wxT("请选择类型"));
        return;
    }

    MONITOR_CENTER *node  = new MONITOR_CENTER ;
    memset(node,0,sizeof(MONITOR_CENTER));
    if(strlen((const char*)TextCtrl_CenterIP->GetValue().mb_str()) <= 64){
        memcpy(node->name,(const char*)TextCtrl_CenterName->GetValue().mb_str(),strlen((const char*)TextCtrl_CenterName->GetValue().mb_str()));
    }
    else{
        wxLogWarning(wxT("字数太长"));
        return;
    }
    memcpy(node->IP,(const char*)TextCtrl_CenterIP->GetValue().mb_str(),strlen((const char*)TextCtrl_CenterIP->GetValue().mb_str()));
    node->port = wxAtoi(TextCtrl_CenterPort->GetValue());
    node->type = Choice_CenterType->GetSelection();

    Ecode_Conv conv;
    string str_name;
    conv.GB2312ToUTF_8(str_name,node->name,64);
    memset(node->name,0,64);
    memcpy(node->name,(char*)str_name.c_str(),strlen((char*)str_name.c_str()));

    printf("%s\n",node->name);
    printf("%s\n",node->IP);
    printf("%d\n",node->port);
    printf("%d\n",node->type);
    monitor = (void*)node;
    EndModal(1);

}

void AddCenterNodeDialog::OnButton_CenterCancelClick(wxCommandEvent& event)     //取消节点操作
{
    EndModal(0);
}

void AddCenterNodeDialog::OnClose(wxCloseEvent& event)
{
   EndModal(0);
}
