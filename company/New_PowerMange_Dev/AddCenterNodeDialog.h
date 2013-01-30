#ifndef ADDCENTERNODEDIALOG_H
#define ADDCENTERNODEDIALOG_H

//(*Headers(AddCenterNodeDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class AddCenterNodeDialog: public wxDialog
{
	public:

		AddCenterNodeDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AddCenterNodeDialog();

		void CenterNodeDialogInit();
		void* Get_Center_Node(){return monitor;};

		//(*Declarations(AddCenterNodeDialog)
		wxButton* Button_CenterSuer;
		wxStaticText* StaticText2;
		wxTextCtrl* TextCtrl_CenterName;
		wxStaticText* StaticText1;
		wxTextCtrl* TextCtrl_CenterPort;
		wxStaticText* StaticText3;
		wxTextCtrl* TextCtrl_CenterIP;
		wxChoice* Choice_CenterType;
		wxButton* Button_CenterCancel;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(AddCenterNodeDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(AddCenterNodeDialog)
		void OnButton_CenterSuerClick(wxCommandEvent& event);
		void OnButton_CenterCancelClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		//*)
		void* monitor;

		DECLARE_EVENT_TABLE()
};

#endif
