#include "LogConfigPanel.h"

//(*InternalHeaders(LogConfigPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(LogConfigPanel)
//*)

BEGIN_EVENT_TABLE(LogConfigPanel,wxPanel)
	//(*EventTable(LogConfigPanel)
	//*)
END_EVENT_TABLE()

LogConfigPanel::LogConfigPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(LogConfigPanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	//*)
}

LogConfigPanel::~LogConfigPanel()
{
	//(*Destroy(LogConfigPanel)
	//*)
}

