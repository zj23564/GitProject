
#include "../LogServerClientMain.h"
#include "../include/Protocol.h"
#include "../include/Define_Log.h"
#include "../include/Define.h"
#include "../include/LogData_Define.h"
#include "../LogConifgure.h"
#include <wx/log.h>
void LogServerClientDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void LogServerClientDialog::OnButton_SerachClick(wxCommandEvent& event)
{
    Clear_LogList();
    search_type = 0;
    dLog.FreeAllLogData();
    HT_READ_QUERY quest;
    memset(&quest,0,sizeof(HT_READ_QUERY));
    LimitLogShow(quest);
    dLog.SendDataPkgToServer(NET_PACKTYPE_LOG_REQUSE_QUERY,(char*)&quest,sizeof(HT_READ_QUERY));

}

//对象类型选择框选中
void LogServerClientDialog::OnChoice_TypeObjSelect(wxCommandEvent& event)
{
    LogObjType* grp = (LogObjType*)event.GetClientData();
    printf("select grp type is %d  name is %s\n",grp->type,grp->name);
    Choice_Type->Clear();
    map<int,LogType*>::iterator ite;
    int n = 0;
    for(ite = dLog.LogType_map.begin();ite!= dLog.LogType_map.end();ite++){
        LogType* type = ite->second;
        if(type->type_obj == grp->type){
            wxString str(type->name,wxConvUTF8);
            printf("GUI type name is %s\n",type->name);
            Choice_Type->Insert(str,n,(void*)type);
            n++;
        }

    }
}

//日志子类型框选中
void LogServerClientDialog::OnChoice_TypeSelect(wxCommandEvent& event)
{
    SetChioceCtrl();
}

//查询起始时间改变事件
void LogServerClientDialog::OnDatePickerCtrl_StartChanged(wxDateEvent& event)
{
    wxDateTime time = event.GetDate();
    time_t tm = time.GetTicks();        //年份时间获取
    int hour = SpinCtrl_Start_hour->GetValue();     //小时
    printf("hour is %d\n",hour);
    int min =  SpinCtrl_Start_min->GetValue();      //分钟
    printf("min is %d\n",min);
    printf("tm is %d\n",tm);
    tm = tm+hour*60*60+min*60;  //选取的起始时间 精确到分钟
    printf("really tm is %d\n",tm);
    //Time_Cov(tm);

}
//查询结束时间改变事件
void LogServerClientDialog::OnDatePickerCtrl_EndChanged(wxDateEvent& event)
{
    wxDateTime time = event.GetDate();
    time_t tm = time.GetTicks();        //年份时间获取
    int hour = SpinCtrl_End_hour->GetValue();     //小时
    printf("hour is %d\n",hour);
    int min =  SpinCtrl_End_min->GetValue();      //分钟
    printf("min is %d\n",min);
    printf("tm is %d\n",tm);
    tm = tm+hour*60*60+min*60;  //选取的结束时间 精确到分钟
    printf("really tm is %d\n",tm);
}


//申请显示实时日志
void LogServerClientDialog::OnButton3Click_ShowRealTimeLog(wxCommandEvent& event)
{
    char* t_log = dLog.GetAllLogAddr();
    if(NULL !=t_log)
        dLog.FreeAllLogData();

    dLog.SendDataPkgToServer(NET_PACKTYPE_LOG_SREACH_REALTIMELOG,NULL,0);
    Clear_LogList();
    printf("dddddd\n");
    StaticText_pageCount->SetLabel(wxString::Format(wxT("共%i页"),1));
    StaticText_pageMark->SetLabel(wxString::Format(wxT("当前第%i页"),1));
    search_type = 1;
}
//日志配置
void LogServerClientDialog::OnButton4Click_ConfigLog(wxCommandEvent& event)
{
    LogConifgure ConfigureGui(0);
    ConfigureGui.GetDataClass(&dLog);
    ConfigureGui.ConfigureInit();
    int ret = ConfigureGui.ShowModal();
    printf("ret is %d\n",ret);
    if(0>ret){
        //<0证明是删除日志类型或者日志源
        printf("delete log source/type \n");
        SetChioceCtrl();
    }
    ConfigureGui.Destroy();

}

//上一页
void LogServerClientDialog::OnButton_upPageClick(wxCommandEvent& event)
{
    Clear_LogList();
    if(search_type == 1){
        wxLogWarning(wxT("已经最上页"));
        return;
    }
    if(page_mark == 0){
        wxLogWarning(wxT("没有日志信息"));
        return;
    }
    if(page_mark == 1){
        wxLogWarning(wxT("已经是第一页"));
    }
    else
        page_mark--;

    int t_log_item_num = 0;
    if(page_mark == page_count)
        t_log_item_num = num_page_lase;
    else
        t_log_item_num = one_page;

    char* pagelog_start = start_log+sizeof(HT_RETURN_LOG)+(page_mark-1)*one_page*sizeof(HT_LOG_ITEM);

    StaticText_pageCount->SetLabel(wxString::Format(wxT("一共%i页"),page_count));
    StaticText_pageMark->SetLabel(wxString::Format(wxT("当前第%i页"),page_mark));

    for(int i = 0;i<t_log_item_num;i++){
        HT_LOG_ITEM * item = (HT_LOG_ITEM*)(pagelog_start+(t_log_item_num-i-1)*sizeof(HT_LOG_ITEM));

        wxString str_type(item->type,wxConvUTF8);
        wxString str_objtype(item->objtype,wxConvUTF8);
        wxString str_obj(item->obj,wxConvUTF8);
        wxString str_log(item->context,wxConvUTF8);

        char* time = Time_Cov(item->time);
        wxString str_time(time,wxConvUTF8);
        wxString str[6] = {wxString::Format(wxT("%i"),((page_mark-1)*one_page)+t_log_item_num-i),str_obj,str_type,str_objtype,str_log,str_time};
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

//下一页
void LogServerClientDialog::OnButton_downPageClick(wxCommandEvent& event)
{
    Clear_LogList();
    if(search_type == 1){
        wxLogWarning(wxT("已经最后一页"));
        return;
    }
    if(page_mark == 0){
        wxLogWarning(wxT("没有日志信息"));
        return;
    }
    if(page_mark == page_count){
        wxLogWarning(wxT("已经是最后一页"));
    }
    else
        page_mark++;

    int t_log_item_num = 0;
    if(page_mark == page_count)
        t_log_item_num = num_page_lase;
    else
        t_log_item_num = one_page;

    char* pagelog_start = start_log+sizeof(HT_RETURN_LOG)+(page_mark-1)*one_page*sizeof(HT_LOG_ITEM);

    StaticText_pageCount->SetLabel(wxString::Format(wxT("一共%i页"),page_count));
    StaticText_pageMark->SetLabel(wxString::Format(wxT("当前第%i页"),page_mark));

    for(int i = 0;i<t_log_item_num;i++){
        HT_LOG_ITEM * item = (HT_LOG_ITEM*)(pagelog_start+(t_log_item_num-i-1)*sizeof(HT_LOG_ITEM));

        wxString str_type(item->type,wxConvUTF8);
        wxString str_objtype(item->objtype,wxConvUTF8);
        wxString str_obj(item->obj,wxConvUTF8);
        wxString str_log(item->context,wxConvUTF8);

        char* time = Time_Cov(item->time);
        wxString str_time(time,wxConvUTF8);
        wxString str[6] = {wxString::Format(wxT("%i"),((page_mark-1)*one_page)+t_log_item_num-i),str_obj,str_type,str_objtype,str_log,str_time};
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






