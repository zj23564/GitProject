#include "../LogServerClientMain.h"
#include <time.h>
void LogServerClientDialog::GuiInit(wxCommandEvent& event)
{
    printf("GUI INIT\n");
    this->SetTitle(wxT("日志服务配置客户端 HT-LS/C For HT-VAIMP V2012"));
    wxString str[6] = {wxT("序号"), wxT("日志源"),wxT("日志类型"),wxT("源类型"),wxT("日志"),wxT("时间")};
    wxListItem item;
    for(int i = 0; i < 6; i++)
    {
        item.SetText(str[i]);
        wxString st=item.GetText();
        ListCtrl_LogList->SetColumn(i,item);
        ListCtrl_LogList->InsertColumn(i,item);
        ListCtrl_LogList->SetColumnWidth(i,70);
    }
    ListCtrl_LogList->SetColumnWidth(0,45);
    ListCtrl_LogList->SetColumnWidth(4,240);

    SetChioceCtrl();
    GetInitStartTime();
    GetInitEndTime();

    one_page = 50;
    page_mark = 0;
    page_count = 0;
    search_type = 0;

}

void LogServerClientDialog::SetChioceCtrl()
{
    int n = 0;
    printf("is here OK\n");
    Choice_TypeObj->Clear();
    map<int,LogObjType*>::iterator ite_grp;

    for(ite_grp = dLog.LogTypeObj_map.begin();ite_grp!= dLog.LogTypeObj_map.end();ite_grp++){
        LogObjType* grp = ite_grp->second;
        wxString str(grp->name,wxConvUTF8);
        printf("GUI grp name is %s\n",grp->name);
        Choice_TypeObj->Insert(str,n,(void*)grp);
        n++;
    }

}
void LogServerClientDialog::Clear_LogList()
{
    ListCtrl_LogList->DeleteAllItems();
}


char* LogServerClientDialog::Time_Cov(int tim)
{
    struct tm * nowtime;
    time_t tt = tim;
    nowtime = localtime(&tt);
    int year = nowtime->tm_year+1900;
    int mon = nowtime->tm_mon+1;
    int day = nowtime->tm_mday;
    int hour = nowtime->tm_hour;
    int min = nowtime->tm_min;
    int sec = nowtime->tm_sec;
    char* time = new char[128];
    memset(time,0,128);
    sprintf(time,"%d-%02d-%02d-%02d:%02d:%02d",year,mon,day,hour,min,sec);
    printf("time is %s\n",time);
    return time;
}

/*******************************************************************************************
当查询日志时还没有选择时间的时候，默认将时间控件上的时间提取下来，如果以后时间有所变化，
再通过控件得到时间
********************************************************************************************/
int LogServerClientDialog::GetInitStartTime()
{
    wxDateTime time = DatePickerCtrl_Start->GetValue();
    time_t tm = time.GetTicks();        //年份时间获取
    int hour = SpinCtrl_Start_hour->GetValue();     //小时
    int min =  SpinCtrl_Start_min->GetValue();      //分钟
    tm = tm+hour*60*60+min*60;  //选取的起始时间 精确到分钟
    return tm;
}

int LogServerClientDialog::GetInitEndTime()
{
    wxDateTime time = DatePickerCtrl_End->GetValue();
    time_t tm = time.GetTicks();        //年份时间获取
    int hour = SpinCtrl_End_hour->GetValue();     //小时
    int min =  SpinCtrl_End_min->GetValue();      //分钟
    tm = tm+hour*60*60+min*60;  //选取的结束时间 精确到分钟
    return tm;
}

void LogServerClientDialog::LimitLogShow(HT_READ_QUERY& query)    //日志通过筛选返回true 否则返回false
{
    query.queryFlag = 0;
   if(CheckBox_obj->IsChecked()){
        if(0 <= Choice_TypeObj->GetSelection()){
            LogObjType* obj = (LogObjType*)(Choice_TypeObj->GetClientData(Choice_TypeObj->GetSelection()));
            query.object = obj->ID;
            printf("query.object is %d\n",query.object);
        }
   }
   if(CheckBox_type->IsChecked()){
        if(0<=Choice_Type->GetSelection()){
            LogType* type = (LogType*)(Choice_Type->GetClientData(Choice_Type->GetSelection()));
            query.type = type->ID;
            printf("query.type is %d\n",query.type);
        }
   }
   if(CheckBox_time->IsChecked()){
        query.starttime = GetInitStartTime();
        query.endtime = GetInitEndTime();
   }
}

