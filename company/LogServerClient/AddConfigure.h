#ifndef ADDCONFIGURE_H
#define ADDCONFIGURE_H

//(*Headers(AddConfigure)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class AddConfigure: public wxDialog
{
	public:

		AddConfigure(wxWindow* parent);
		virtual ~AddConfigure();
		//void SetItemArray(wxArrayString& item){itemArr = item;};
        wxArrayString GetItemArray(){return itemArr;}
		//(*Declarations(AddConfigure)
		wxTextCtrl* TextCtrl_Items;
		wxButton* Button_Sure;
		wxStaticText* StaticText1;
		wxButton* Button_Cancel;
		//*)

	protected:

		//(*Identifiers(AddConfigure)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(AddConfigure)
		void OnButton_SureClick(wxCommandEvent& event);
		//*)

		wxArrayString itemArr;

		DECLARE_EVENT_TABLE()
};

#endif
