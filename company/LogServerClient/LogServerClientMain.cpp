/***************************************************************
 * Name:      LogServerClientMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    zj ()
 * Created:   2012-11-15
 * Copyright: zj ()
 * License:
 **************************************************************/

#include "LogServerClientMain.h"
#include <wx/msgdlg.h>
#include "include/Protocol.h"
#include "include/log_client_define.h"
#include <wx/log.h>
//(*InternalHeaders(LogServerClientDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <stdio.h>
//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

void DataGuiCallBack(void *gui,void* data,int command);

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

//(*IdInit(LogServerClientDialog)
const long LogServerClientDialog::ID_LISTCTRL1 = wxNewId();
const long LogServerClientDialog::ID_STATICTEXT1 = wxNewId();
const long LogServerClientDialog::ID_STATICTEXT2 = wxNewId();
const long LogServerClientDialog::ID_BUTTON1 = wxNewId();
const long LogServerClientDialog::ID_BUTTON2 = wxNewId();
const long LogServerClientDialog::ID_CHECKBOX2 = wxNewId();
const long LogServerClientDialog::ID_CHOICE2 = wxNewId();
const long LogServerClientDialog::ID_CHECKBOX3 = wxNewId();
const long LogServerClientDialog::ID_CHOICE3 = wxNewId();
const long LogServerClientDialog::ID_CHECKBOX4 = wxNewId();
const long LogServerClientDialog::ID_DATEPICKERCTRL1 = wxNewId();
const long LogServerClientDialog::ID_SPINCTRL1 = wxNewId();
const long LogServerClientDialog::ID_SPINCTRL2 = wxNewId();
const long LogServerClientDialog::ID_DATEPICKERCTRL2 = wxNewId();
const long LogServerClientDialog::ID_SPINCTRL4 = wxNewId();
const long LogServerClientDialog::ID_SPINCTRL3 = wxNewId();
const long LogServerClientDialog::ID_BUTTON3 = wxNewId();
const long LogServerClientDialog::ID_BUTTON4 = wxNewId();
const long LogServerClientDialog::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LogServerClientDialog,wxDialog)
    //(*EventTable(LogServerClientDialog)
    //*)

    EVT_MENU(ID_SERACH, LogServerClientDialog::GetAllLog)
    EVT_MENU(ID_REALTIMELOG, LogServerClientDialog::GetRealTimeLog)
    EVT_MENU(ID_ADDTYPE, LogServerClientDialog::GetAddEvent)
    EVT_MENU(ID_GUIINIT, LogServerClientDialog::GuiInit)
END_EVENT_TABLE()

LogServerClientDialog::LogServerClientDialog(char* serverIP,int serverPort,wxWindow* parent,wxWindowID id):dLog(serverIP,serverPort)
{
    //(*Initialize(LogServerClientDialog)
    wxBoxSizer* BoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer8;
    wxFlexGridSizer* FlexGridSizer3;
    wxStaticBoxSizer* StaticBoxSizer9;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer12;
    wxStaticBoxSizer* StaticBoxSizer8;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxBoxSizer* BoxSizer9;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer5;

    Create(parent, wxID_ANY, _("HT-LS V2012"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    FlexGridSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
    FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("日志查询结果"));
    ListCtrl_LogList = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxSize(608,500), wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL1"));
    StaticBoxSizer1->Add(ListCtrl_LogList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(StaticBoxSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2->Add(BoxSizer3, 2, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_pageMark = new wxStaticText(this, ID_STATICTEXT1, _("当前第1页"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
    BoxSizer2->Add(StaticText_pageMark, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText_pageCount = new wxStaticText(this, ID_STATICTEXT2, _("共1页"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer2->Add(StaticText_pageCount, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_upPage = new wxButton(this, ID_BUTTON1, _("上一页"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button_upPage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_downPage = new wxButton(this, ID_BUTTON2, _("下一页"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer2->Add(Button_downPage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("查询条件"));
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("源类型"));
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    CheckBox_obj = new wxCheckBox(this, ID_CHECKBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox_obj->SetValue(false);
    BoxSizer8->Add(CheckBox_obj, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice_TypeObj = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    BoxSizer8->Add(Choice_TypeObj, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer5->Add(BoxSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(StaticBoxSizer5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("日志类型"));
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    CheckBox_type = new wxCheckBox(this, ID_CHECKBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBox_type->SetValue(false);
    BoxSizer9->Add(CheckBox_type, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice_Type = new wxChoice(this, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    BoxSizer9->Add(Choice_Type, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6->Add(BoxSizer9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(StaticBoxSizer6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("查询时间条件"));
    StaticBoxSizer8 = new wxStaticBoxSizer(wxVERTICAL, this, _("起始时间"));
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    CheckBox_time = new wxCheckBox(this, ID_CHECKBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBox_time->SetValue(false);
    BoxSizer10->Add(CheckBox_time, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DatePickerCtrl_Start = new wxDatePickerCtrl(this, ID_DATEPICKERCTRL1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL1"));
    BoxSizer10->Add(DatePickerCtrl_Start, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer8->Add(BoxSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    SpinCtrl_Start_hour = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxSize(50,20), 0, 0, 23, 0, _T("ID_SPINCTRL1"));
    SpinCtrl_Start_hour->SetValue(_T("0"));
    BoxSizer11->Add(SpinCtrl_Start_hour, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_Start_min = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxSize(50,20), 0, 0, 59, 0, _T("ID_SPINCTRL2"));
    SpinCtrl_Start_min->SetValue(_T("0"));
    BoxSizer11->Add(SpinCtrl_Start_min, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer8->Add(BoxSizer11, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(StaticBoxSizer8, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer9 = new wxStaticBoxSizer(wxVERTICAL, this, _("结束时间"));
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    DatePickerCtrl_End = new wxDatePickerCtrl(this, ID_DATEPICKERCTRL2, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL2"));
    BoxSizer5->Add(DatePickerCtrl_End, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer9->Add(BoxSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    SpinCtrl_End_hour = new wxSpinCtrl(this, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxSize(50,20), 0, 0, 23, 0, _T("ID_SPINCTRL4"));
    SpinCtrl_End_hour->SetValue(_T("0"));
    BoxSizer12->Add(SpinCtrl_End_hour, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl_End_min = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxSize(50,20), 0, 0, 59, 0, _T("ID_SPINCTRL3"));
    SpinCtrl_End_min->SetValue(_T("0"));
    BoxSizer12->Add(SpinCtrl_End_min, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer9->Add(BoxSizer12, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(StaticBoxSizer9, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(StaticBoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    Button_Serach = new wxButton(this, ID_BUTTON3, _("查询"), wxDefaultPosition, wxSize(50,30), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer6->Add(Button_Serach, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(this, ID_BUTTON4, _("实时日志"), wxDefaultPosition, wxSize(50,30), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer6->Add(Button3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button4 = new wxButton(this, ID_BUTTON5, _("配置"), wxDefaultPosition, wxSize(50,30), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer6->Add(Button4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(FlexGridSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogServerClientDialog::OnButton_upPageClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogServerClientDialog::OnButton_downPageClick);
    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&LogServerClientDialog::OnChoice_TypeObjSelect);
    Connect(ID_DATEPICKERCTRL1,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&LogServerClientDialog::OnDatePickerCtrl_StartChanged);
    Connect(ID_DATEPICKERCTRL2,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&LogServerClientDialog::OnDatePickerCtrl_EndChanged);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogServerClientDialog::OnButton_SerachClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogServerClientDialog::OnButton3Click_ShowRealTimeLog);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogServerClientDialog::OnButton4Click_ConfigLog);
    //*)

    dLog.setContext(this);
    //设置数据回调
    dLog.setCallback(DataGuiCallBack);

    if(dLog.NetInit()){
        dLog.ReqLogTypeObj();
        dLog.ReqLogType();
    }
    else{
        wxLogMessage(wxT("连接日志服务器失败"));
        return;
    }

    wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,ID_GUIINIT);
    wxPostEvent(this,event);





}
LogServerClientDialog::~LogServerClientDialog()
{

    //(*Destroy(LogServerClientDialog)
    //*)
}
void LogServerClientDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


void DataGuiCallBack(void *gui,void* data,int command)
{
    LogServerClientDialog* t_gui = (LogServerClientDialog*)gui;
    switch(command){
        case DATA_TO_GUI_COMMAND_LOG_DATA:{
            wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,ID_SERACH);
           // printf("context %d\n",data);
            event.SetInt((int)(data+sizeof(HEAD)));
            wxPostEvent(t_gui,event);
            break;
        }
        case DATA_TO_GUI_COMMAND_OK_GUIINIT:{
            printf("hree\n");
            break;
        }
        case DATA_TO_GUI_COMMAND_REALTIMELOG:{
            wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,ID_REALTIMELOG);
            printf("context %d\n",data);
            event.SetInt((int)(data));
            wxPostEvent(t_gui,event);
            break;
        }
        case DATA_TO_GUI_COMMAND_ADDSOURCETYPE:{
            wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,ID_ADDTYPE);
            wxPostEvent(t_gui,event);
            break;
        }
        case DATA_TO_GUI_COMMAND_ADDLOGTYPE:{
            wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,ID_ADDTYPE);
            wxPostEvent(t_gui,event);
            break;
        }
        case DATA_TO_GUI_COMMAND_CONNECTSERVERERROR:{
            wxLogMessage(wxT("连接日志服务器失败"));
            break;
        }
        case DATA_TO_GUI_COMMAND_LOGSEVERCLOSE:{
            wxLogMessage(wxT("日志服务器断开连接，客户端将不再能获取到日志更新信息"));
            break;
        }
        default:
            break;
    }

}

