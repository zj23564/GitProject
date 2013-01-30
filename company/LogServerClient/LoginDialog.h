#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

//(*Headers(LoginDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class LoginDialog: public wxDialog
{
	public:

		LoginDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~LoginDialog();
		char* GetServerIP(){return serverIP;}
		int GetServerPort(){return serverPort;}

		//(*Declarations(LoginDialog)
		wxStaticText* StaticText2;
		wxButton* Button_Sure;
		wxTextCtrl* TextCtrl_Sport;
		wxStaticText* StaticText1;
		wxButton* Button_Cancel;
		wxTextCtrl* TextCtrl_Sip;
		//*)

	protected:

		//(*Identifiers(LoginDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(LoginDialog)
		void OnButton_SureClick(wxCommandEvent& event);
		void OnButton_CancelClick(wxCommandEvent& event);
		//*)

		char serverIP[16];
		int serverPort;

		DECLARE_EVENT_TABLE()
};

#endif
