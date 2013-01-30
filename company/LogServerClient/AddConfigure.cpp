#include "AddConfigure.h"
#include <stdio.h>
//(*InternalHeaders(AddConfigure)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(AddConfigure)
const long AddConfigure::ID_STATICTEXT1 = wxNewId();
const long AddConfigure::ID_TEXTCTRL1 = wxNewId();
const long AddConfigure::ID_BUTTON2 = wxNewId();
const long AddConfigure::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AddConfigure,wxDialog)
	//(*EventTable(AddConfigure)
	//*)
END_EVENT_TABLE()

AddConfigure::AddConfigure(wxWindow* parent)
{
	//(*Initialize(AddConfigure)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("回车换行输入多行可以一次性插入多条数据"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Items = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(205,193), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer1->Add(TextCtrl_Items, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	Button_Sure = new wxButton(this, ID_BUTTON2, _("确认"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(Button_Sure, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button_Cancel = new wxButton(this, ID_BUTTON1, _("取消"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(Button_Cancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AddConfigure::OnButton_SureClick);
	//*)
}

AddConfigure::~AddConfigure()
{
	//(*Destroy(AddConfigure)
	//*)
}


void AddConfigure::OnButton_SureClick(wxCommandEvent& event)
{
    int num = TextCtrl_Items->GetNumberOfLines();
    for(int i = 0;i<num;i++){
        if((TextCtrl_Items->GetLineText(i)).IsEmpty())
            continue;
        itemArr.Add(TextCtrl_Items->GetLineText(i));
    }
    EndModal(1);
}
