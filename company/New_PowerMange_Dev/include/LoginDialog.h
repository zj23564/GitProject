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
		void GuiInit();
		int Open_ConfigFile(const char* name,const char* passwd);
		char* GetServerIP(){return serverIP;}
		int GetServerPort(){return serverPort;}

		//(*Declarations(LoginDialog)
		wxButton* Button_cancel;
		wxTextCtrl* TextCtrl_Name;
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* Button_Login;
		wxTextCtrl* TextCtrl_IP;
		wxTextCtrl* TextCtrl_Port;
		wxTextCtrl* TextCtrl_Passwd;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(LoginDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(LoginDialog)
		void OnButton_LoginClick(wxCommandEvent& event);
		void OnButton_cancelClick(wxCommandEvent& event);
		//*)
        char serverIP[16];
        int serverPort;
		DECLARE_EVENT_TABLE()
};

#endif
