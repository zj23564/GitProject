#include "AddChannelDialog.h"

//(*InternalHeaders(AddChannelDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include "include/data/Define_Data.h"
//(*IdInit(AddChannelDialog)
const long AddChannelDialog::ID_STATICTEXT1 = wxNewId();
const long AddChannelDialog::ID_TEXTCTRL1 = wxNewId();
const long AddChannelDialog::ID_BUTTON1 = wxNewId();
const long AddChannelDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AddChannelDialog,wxDialog)
	//(*EventTable(AddChannelDialog)
	//*)
END_EVENT_TABLE()

AddChannelDialog::AddChannelDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(AddChannelDialog)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,207));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("channel"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Channel = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(TextCtrl_Channel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	Button_SureAddChannel = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer3->Add(Button_SureAddChannel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button_CancelAddChannel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer3->Add(Button_CancelAddChannel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AddChannelDialog::OnButton_SureAddChannelClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AddChannelDialog::OnButton_CancelAddChannelClick);
	//*)
}

AddChannelDialog::~AddChannelDialog()
{
	//(*Destroy(AddChannelDialog)
	//*)
}


void AddChannelDialog::OnButton_SureAddChannelClick(wxCommandEvent& event)
{
    wxString temp = TextCtrl_Channel->GetValue();
  //  wxString temp1 = TextCtrl_IP->GetValue();
   // wxString temp2 = TextCtrl_Port->GetValue();
    m_name = temp;
//    m_retain1 = temp1;
//    m_retain2 = temp2;
    EndModal(1);
}

void AddChannelDialog::OnButton_CancelAddChannelClick(wxCommandEvent& event)
{
    EndModal(0);
}
