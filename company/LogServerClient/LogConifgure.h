#ifndef LOGCONIFGURE_H
#define LOGCONIFGURE_H

//(*Headers(LogConifgure)
#include <wx/sizer.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)
#include "include/DataLog.h"
#include "include/LogData_Define.h"
class LogConifgure: public wxDialog
{
	public:

		LogConifgure(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~LogConifgure();
		void GetDataClass(DataLog* data){logData = data;}
        void ConfigureInit();
		void SetSourceTypeGui();

		//(*Declarations(LogConifgure)
		wxListBox* ListBox_SourceType;
		wxButton* Button_DelLogType;
		wxButton* Button_AddSourceType;
		wxButton* Button_AddType;
		wxButton* Button_DelSourceType;
		wxListBox* ListBox_LogType;
		//*)

	protected:

		//(*Identifiers(LogConifgure)
		static const long ID_LISTBOX1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_LISTBOX2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		//*)

	private:

		//(*Handlers(LogConifgure)
		void OnListBox_SourceTypeSelect(wxCommandEvent& event);
		void OnButton_AddSourceClick(wxCommandEvent& event);
		void OnButton_DelSourceClick(wxCommandEvent& event);
		void OnButton_AddTypeClick(wxCommandEvent& event);
		void OnButton_DelTypeClick(wxCommandEvent& event);
		void OnButton_SureAddLogTypeClick(wxCommandEvent& event);
		//*)

		DataLog* logData;

		DECLARE_EVENT_TABLE()
};

#endif
