#ifndef LOGCONFIGPANEL_H
#define LOGCONFIGPANEL_H

//(*Headers(LogConfigPanel)
#include <wx/panel.h>
//*)

class LogConfigPanel: public wxPanel
{
	public:

		LogConfigPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~LogConfigPanel();

		//(*Declarations(LogConfigPanel)
		//*)

	protected:

		//(*Identifiers(LogConfigPanel)
		//*)

	private:

		//(*Handlers(LogConfigPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
