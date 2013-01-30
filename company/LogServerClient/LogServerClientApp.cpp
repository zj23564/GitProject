/***************************************************************
 * Name:      LogServerClientApp.cpp
 * Purpose:   Code for Application Class
 * Author:    zj ()
 * Created:   2012-11-15
 * Copyright: zj ()
 * License:
 **************************************************************/

#include "LogServerClientApp.h"
#include "LoginDialog.h"
//(*AppHeaders
#include "LogServerClientMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(LogServerClientApp);

bool LogServerClientApp::OnInit()
{


    LoginDialog lgdlg(0);
    lgdlg.ShowModal();
  //  Dlg = new LogServerClientDialog(lgdlg.GetServerIP(),lgdlg.GetServerPort(),NULL);
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	LogServerClientDialog Dlg(lgdlg.GetServerIP(),lgdlg.GetServerPort(),NULL);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
