#ifndef ADDCHANNELDIALOG_H
#define ADDCHANNELDIALOG_H

//(*Headers(AddChannelDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class AddChannelDialog: public wxDialog
{
	public:

		AddChannelDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~AddChannelDialog();
		wxString GetName(){return m_name;}
	//	wxString GetRetain1(){return m_retain1;}
	//	wxString GetRetain2(){return m_retain2;}

		//(*Declarations(AddChannelDialog)
		wxTextCtrl* TextCtrl_Channel;
		wxStaticText* StaticText1;
		wxButton* Button_SureAddChannel;
		wxButton* Button_CancelAddChannel;
		//*)

	protected:

		//(*Identifiers(AddChannelDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(AddChannelDialog)
		void OnButton_SureAddChannelClick(wxCommandEvent& event);
		void OnButton_CancelAddChannelClick(wxCommandEvent& event);
		//*)
		wxString m_name;
//		wxString m_retain1;
//        wxString m_retain2;
		DECLARE_EVENT_TABLE()
};

#endif
