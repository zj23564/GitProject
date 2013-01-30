/***************************************************************
 * Name:      New_PowerMangerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    zj ()
 * Created:   2012-07-13
 * Copyright: zj ()
 * License:
 **************************************************************/

#include "New_PowerMangerApp.h"
#include "include/LoginDialog.h"
//(*AppHeaders
#include "New_PowerMangerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(New_PowerMangerApp);
New_PowerMangerFrame* Frame;
bool New_PowerMangerApp::OnInit()
{
    LoginDialog  login(0);
    login.ShowModal();

    Frame = new New_PowerMangerFrame(0);
    printf("***************************\n");
    Frame->SetMcsIp(login.GetServerIP());
    Frame->SetMcsPort(login.GetServerPort());


    Frame->NetInit();
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
