#include "LogConifgure.h"

//(*InternalHeaders(LogConifgure)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include "AddConfigure.h"
#include "include/Protocol.h"
#include "include/Define.h"
#include <wx/strconv.h>
#include <wx/log.h>
#include <wx/msgdlg.h>
//(*IdInit(LogConifgure)
const long LogConifgure::ID_LISTBOX1 = wxNewId();
const long LogConifgure::ID_BUTTON1 = wxNewId();
const long LogConifgure::ID_BUTTON2 = wxNewId();
const long LogConifgure::ID_LISTBOX2 = wxNewId();
const long LogConifgure::ID_BUTTON3 = wxNewId();
const long LogConifgure::ID_BUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LogConifgure,wxDialog)
	//(*EventTable(LogConifgure)
	//*)
END_EVENT_TABLE()

LogConifgure::LogConifgure(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(LogConifgure)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("源类型"));
	ListBox_SourceType = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(257,168), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	StaticBoxSizer1->Add(ListBox_SourceType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	Button_AddSourceType = new wxButton(this, ID_BUTTON1, _("add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(Button_AddSourceType, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button_DelSourceType = new wxButton(this, ID_BUTTON2, _("delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(Button_DelSourceType, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("日志类型"));
	ListBox_LogType = new wxListBox(this, ID_LISTBOX2, wxDefaultPosition, wxSize(270,170), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX2"));
	StaticBoxSizer2->Add(ListBox_LogType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	Button_AddType = new wxButton(this, ID_BUTTON3, _("add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer3->Add(Button_AddType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button_DelLogType = new wxButton(this, ID_BUTTON4, _("delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer3->Add(Button_DelLogType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(BoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&LogConifgure::OnListBox_SourceTypeSelect);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogConifgure::OnButton_AddSourceClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogConifgure::OnButton_DelSourceClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogConifgure::OnButton_AddTypeClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogConifgure::OnButton_DelTypeClick);
	//*)
}

LogConifgure::~LogConifgure()
{
	//(*Destroy(LogConifgure)
	//*)
}

void LogConifgure::ConfigureInit()
{
    SetSourceTypeGui();
}

void LogConifgure::SetSourceTypeGui()
{
    map<int,LogObjType*>::iterator item;
    for(item = logData->LogTypeObj_map.begin();item!= logData->LogTypeObj_map.end();item++){
        LogObjType* source = item->second;
        wxString str(source->name,wxConvUTF8);
        ListBox_SourceType->Append(str,(void*)source);
    }

}

void LogConifgure::OnListBox_SourceTypeSelect(wxCommandEvent& event)
{
    ListBox_LogType->Clear();
    LogObjType* source = (LogObjType*)(ListBox_SourceType->GetClientData(event.GetSelection()));

    map<int,LogType*>::iterator item;
    for(item = logData->LogType_map.begin();item!=logData->LogType_map.end();item++){
       LogType* t_log = item->second;
       if(t_log->type_obj == source->type){
            wxString str(t_log->name,wxConvUTF8);
            ListBox_LogType->Append(str,(void*)t_log);
       }
    }
}

void LogConifgure::OnButton_AddSourceClick(wxCommandEvent& event)
{

    wxArrayString itemArr;
    AddConfigure addCnf(0);

    if(addCnf.ShowModal()){
        itemArr = addCnf.GetItemArray();
        int len = sizeof(LogObjType)*itemArr.size();
        char* buff = new char[len];
        memset(buff,0,len);
        for(int i = 0;i<itemArr.size();i++){
            wxString str = itemArr.Item(i);
            wxCharBuffer buffer=str.ToUTF8();
            memcpy(((LogObjType*)(buff+i*sizeof(LogObjType)))->name,buffer.data(),strlen(buffer.data()));
        }
        logData->SendDataPkgToServer(NET_PACKTYPE_LOG_ADDSOURCETYPE,buff,len);
        delete [] buff;
    }
    addCnf.Destroy();
    EndModal(1);

}

void LogConifgure::OnButton_AddTypeClick(wxCommandEvent& event)
{
    if(ListBox_SourceType->GetSelection()<0){
        wxLogWarning(wxT("请在左边选择新日志类型所属的源类型"));
        return;
    }
    LogObjType* t_source = (LogObjType*)(ListBox_SourceType->GetClientData(ListBox_SourceType->GetSelection()));

    wxArrayString itemArr;
    AddConfigure addCnf(0);
    if(addCnf.ShowModal()){
        itemArr = addCnf.GetItemArray();
        printf("out arry size is %d\n",itemArr.size());
        int len = sizeof(LogType)*itemArr.size();
        char* buff = new char[len];
        memset(buff,0,len);
        for(int i = 0;i<itemArr.size();i++){
            wxString str = itemArr.Item(i);
            wxCharBuffer buffer=str.ToUTF8();
            memcpy(((LogType*)(buff+i*sizeof(LogType)))->name,buffer.data(),strlen(buffer.data()));

            ((LogType*)(buff+i*sizeof(LogType)))->type_obj = t_source->type;
            printf("buff is %s\n",((LogType*)(buff+i*sizeof(LogType)))->name);

        }
        logData->SendDataPkgToServer(NET_PACKTYPE_LOG_ADDLOGTYPE,buff,len);
        delete [] buff;
    }
    addCnf.Destroy();
    EndModal(1);
}

void LogConifgure::OnButton_DelSourceClick(wxCommandEvent& event)
{
    if(ListBox_SourceType->GetSelection()<0){
        wxLogWarning(wxT("请选择将要删除的日志源类型"));
        return;
    }
    LogObjType* t_source = (LogObjType*)(ListBox_SourceType->GetClientData(ListBox_SourceType->GetSelection()));

    map<int,LogObjType*>::iterator item;
    item = logData->LogTypeObj_map.find(t_source->type);
    if(item != logData->LogTypeObj_map.end()){
        int ret = wxMessageBox(wxT("删除日志源类型同时将删除源类型下所有的日志类型"),wxT("确认提示"),wxYES_NO);
        if(ret == wxNO){
            printf("取消删除日志源类型节点\n");
            return ;
        }

        logData->LogTypeObj_map.erase(item);


        //删除日志源类型下所有日志类型
        map<int,LogType*>::iterator item;
        for(item = logData->LogType_map.begin();item!=logData->LogType_map.end();){
           LogType* t_log = item->second;
           if(t_log->type_obj == t_source->type){
                map<int,LogType*>::iterator t_item;
                t_item = item;
                ++item;
                logData->LogType_map.erase(t_item);
                delete t_log;
           }
           else
            item++;
        }
        logData->SendDataPkgToServer(NET_PACKTYPE_LOG_DELSOURCETYPE,(char*)t_source,sizeof(LogObjType));
    }
    else
        wxLogWarning(wxT("找不到删除的数据内容"));

    delete t_source;
    EndModal(-1);

}

void LogConifgure::OnButton_DelTypeClick(wxCommandEvent& event)
{
    if(ListBox_LogType->GetSelection()<0){
        wxLogWarning(wxT("请选择将要删除的日志类型"));
        return;
    }
    LogType* t_type = (LogType*)(ListBox_LogType->GetClientData(ListBox_LogType->GetSelection()));

    map<int,LogType*>::iterator item;
    item = logData->LogType_map.find(t_type->ID);

    if(item != logData->LogType_map.end()){
        int ret = wxMessageBox(wxT("确认删除日志类型"),wxT("确认提示"),wxYES_NO);
        if(ret == wxNO){
            printf("取消删除日志类型\n");
            return ;
        }

        logData->LogType_map.erase(item);


        logData->SendDataPkgToServer(NET_PACKTYPE_LOG_DELLOGTYPE,(char*)t_type,sizeof(LogType));
    }
    else
        wxLogWarning(wxT("找不到删除的数据内容"));
    delete item->second;

    EndModal(-1);
}

