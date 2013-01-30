#include "../LogServerClientMain.h"
#include "../include/DataLog.h"
#include "../include/LogData_Define.h"

void LogServerClientDialog::GetAllLog(wxCommandEvent& event)
{

    HT_RETURN_LOG* log_head = (HT_RETURN_LOG*)(event.GetInt());
    start_log = (char*)(event.GetInt());
    if(0 == (log_head->totalnum)%one_page){
        page_count = (log_head->totalnum)/one_page;
        num_page_lase = one_page;
    }
    else{
        page_count = (log_head->totalnum)/one_page + 1;
        num_page_lase = (log_head->totalnum)%one_page;
    }

    page_mark = 1;  //每次新查询，都将页面置为第一页

    int t_log_item_num = 0;;
    if(log_head->totalnum < one_page)
        t_log_item_num = log_head->totalnum;
    else
        t_log_item_num = one_page;

    if(page_count == 0)
        StaticText_pageCount->SetLabel(wxString::Format(wxT("一共%i页"),1));
    else
        StaticText_pageCount->SetLabel(wxString::Format(wxT("一共%i页"),page_count));
    StaticText_pageMark->SetLabel(wxString::Format(wxT("当前第%i页"),page_mark));

    if(0 == log_head->totalnum)
        page_mark = 0;

    for(int i = 0;i<t_log_item_num;i++){
        HT_LOG_ITEM * item = (HT_LOG_ITEM*)((start_log+sizeof(HT_RETURN_LOG))+(t_log_item_num-i-1)*sizeof(HT_LOG_ITEM));

        wxString str_type(item->type,wxConvUTF8);
        wxString str_objtype(item->objtype,wxConvUTF8);
        wxString str_obj(item->obj,wxConvUTF8);
        wxString str_log(item->context,wxConvUTF8);

        char* time = Time_Cov(item->time);
        wxString str_time(time,wxConvUTF8);
        wxString str[6] = {wxString::Format(wxT("%i"),t_log_item_num-i),str_obj,str_type,str_objtype,str_log,str_time};
        wxListItem it;
        ListCtrl_LogList->InsertItem(0,it);
        for(int j = 0;j<6;j++){
            it.SetColumn(j);
            it.SetText(str[j]);
            ListCtrl_LogList->SetItem(it);
        }
        delete [] time;

    }

}

void LogServerClientDialog::GetRealTimeLog(wxCommandEvent& event)   //实时日志
{
    printf("real time log event\n");
    Choice_Type->Clear();
    StaticText_pageCount->SetLabel(wxString::Format(wxT("一共%i页"),1));
    StaticText_pageCount->SetLabel(wxString::Format(wxT("一共%i页"),1));
    HT_LOG_ITEM* item = (HT_LOG_ITEM*)(event.GetInt());
   // wxString str_typegrp(item->typegrp,wxConvUTF8);
    wxString str_type(item->type,wxConvUTF8);
    wxString str_objtype(item->objtype,wxConvUTF8);
    wxString str_obj(item->obj,wxConvUTF8);
    wxString str_log(item->context,wxConvUTF8);
    char* time = Time_Cov(item->time);
    wxString str_time(time,wxConvUTF8);
    int t_count = ListCtrl_LogList->GetItemCount();
    wxString str[6] = {wxString::Format(wxT("%i"),t_count+1),str_obj,str_type,str_objtype,str_log,str_time};
    wxListItem it;
    ListCtrl_LogList->InsertItem(0,it);
    for(int j = 0;j<6;j++){
        it.SetColumn(j);
        it.SetText(str[j]);
        ListCtrl_LogList->SetItem(it);
    }

}

void LogServerClientDialog::GetAddEvent(wxCommandEvent& event)
{
    printf("add type event start\n");
    SetChioceCtrl();
}

