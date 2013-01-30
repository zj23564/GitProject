/***************************************************************
 * Name:      LogServerClientMain.h
 * Purpose:   Defines Application Frame
 * Author:    zj ()
 * Created:   2012-11-15
 * Copyright: zj ()
 * License:
 **************************************************************/

#ifndef LOGSERVERCLIENTMAIN_H
#define LOGSERVERCLIENTMAIN_H

//(*Headers(LogServerClientDialog)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/checkbox.h>
#include <wx/datectrl.h>
#include <wx/spinctrl.h>
#include <wx/dateevt.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)
#include "include/DataLog.h"

enum
{
    ID_SERACH = 20000,
    ID_REALTIMELOG = 20001,
    ID_ADDTYPE = 20002,
    ID_GUIINIT = 20003,
};
class LogServerClientDialog: public wxDialog
{
    public:

        LogServerClientDialog(char* serverIP,int serverPort,wxWindow* parent,wxWindowID id = -1);
        virtual ~LogServerClientDialog();
        DataLog dLog;  //实例化数据类

        char* Time_Cov(int tim);
        void SetChioceCtrl();
        int GetInitStartTime();
        int GetInitEndTime();
        void LimitLogShow(HT_READ_QUERY& query);   //将日志放入查询条件中筛选
        void Clear_LogList();   //清楚在日志列表中的消息


    private:

        //(*Handlers(LogServerClientDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton_SerachClick(wxCommandEvent& event);
        void OnChoice_TypeGrpSelect(wxCommandEvent& event);
        void OnChoice_TypeSelect(wxCommandEvent& event);
        void OnDatePickerCtrl_StartChanged(wxDateEvent& event);
        void OnDatePickerCtrl_EndChanged(wxDateEvent& event);
        void OnButton3Click_ShowRealTimeLog(wxCommandEvent& event);
        void OnChoice_TypeObjSelect(wxCommandEvent& event);
        void OnButton4Click_ConfigLog(wxCommandEvent& event);
        void OnButton_downPageClick(wxCommandEvent& event);
        void OnButton_upPageClick(wxCommandEvent& event);
        //*)
        void GetAllLog(wxCommandEvent& event);
        void GetRealTimeLog(wxCommandEvent& event);
        void GetAddEvent(wxCommandEvent& event);
        void GuiInit(wxCommandEvent& event);

        //(*Identifiers(LogServerClientDialog)
        static const long ID_LISTCTRL1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_CHECKBOX2;
        static const long ID_CHOICE2;
        static const long ID_CHECKBOX3;
        static const long ID_CHOICE3;
        static const long ID_CHECKBOX4;
        static const long ID_DATEPICKERCTRL1;
        static const long ID_SPINCTRL1;
        static const long ID_SPINCTRL2;
        static const long ID_DATEPICKERCTRL2;
        static const long ID_SPINCTRL4;
        static const long ID_SPINCTRL3;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        //*)

        //(*Declarations(LogServerClientDialog)
        wxCheckBox* CheckBox_obj;
        wxCheckBox* CheckBox_type;
        wxMenu Menu1;
        wxButton* Button4;
        wxSpinCtrl* SpinCtrl_End_min;
        wxSpinCtrl* SpinCtrl_End_hour;
        wxStaticText* StaticText_pageMark;
        wxButton* Button_Serach;
        wxCheckBox* CheckBox_time;
        wxButton* Button_downPage;
        wxStaticText* StaticText_pageCount;
        wxSpinCtrl* SpinCtrl_Start_hour;
        wxButton* Button3;
        wxDatePickerCtrl* DatePickerCtrl_End;
        wxBoxSizer* BoxSizer1;
        wxButton* Button_upPage;
        wxChoice* Choice_TypeObj;
        wxChoice* Choice_Type;
        wxSpinCtrl* SpinCtrl_Start_min;
        wxListCtrl* ListCtrl_LogList;
        wxDatePickerCtrl* DatePickerCtrl_Start;
        //*)

        int page_count;       //日志页总数
        int page_mark;      //日志当前页
        int one_page;       //日志一页日志数量
        int num_page_lase;  //最后一页日志数量

        char* start_log;       //日志数据起始地址 日志头+日志
        int search_type;        //0 日志查询  1 实时日志查询



        DECLARE_EVENT_TABLE()
};

#endif // LOGSERVERCLIENTMAIN_H
