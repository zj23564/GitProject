#include "../../New_PowerMangerMain.h"

#include "../../include/Tree/CGreatTree.h"

#include "../../include/define/Define_Page.h"
#include "../../include/data/Define_Data.h"
#include "../../include/define/Define.h"
#include "../../include/encode_conv/Ecode_Conv.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include <wx/icon.h>
#include <wx/msgdlg.h>
#include "../checked.xpm"
#include "../unchecked.xpm"
#include <map>
#include <wx/log.h>
#include <iostream>
using namespace std;
extern New_PowerMangerFrame* Frame;

void New_PowerMangerFrame::Page_AddDeviceNode()
{
    Notebook1->SetSelection(2);
    Enable_DevGui();
}

void New_PowerMangerFrame::Set_ChannelList(int num)        //增加设备节点前的清屏工作
{

    /**********初始化通道表格中数据***********/

    char tmp[16] = "channel";
    char status[16] = "off";
    int port = 8000;
    char name[64] = {0};

    for(int i = 0;i<num;i++){
        sprintf(name,"%s%d",tmp,num-i);
        wxString str_name(name,wxConvUTF8);
        wxString str_status(status,wxConvUTF8);
//        wxString str_port;
//        str_port<<port;
        printf("*******************\n");
        wxString str[2] = {str_name,str_status};
        wxListItem it;
        ListCtrl_Channel->InsertItem(0,it);
        for(int j = 0;j<2;j++){
            it.SetColumn(j);
            it.SetText(str[j]);
            ListCtrl_Channel->SetItem(it);
        }
    }


}
void New_PowerMangerFrame::UpdateDevOnTree(char* data)
{
    DEVICE* dev = (DEVICE*)data;
    int channel_count = 0;
    switch(dev->type ){
        case DEVICE_TYPE_HK:channel_count = 4;break;
        case DEVICE_TYPE_GH:channel_count = 0;break;
        case DEVICE_TYPE_HB:channel_count = 16;break;
        case DEVICE_TYPE_DH:channel_count = 0;break;
        case DEVICE_TYPE_JG:channel_count = 0;break;
        case DEVICE_TYPE_WD:channel_count = 0;break;
        case DEVICE_TYPE_DJL:channel_count = 0;break;
        case DEVICE_TYPE_WL:channel_count = 0;break;
        case DEVICE_TYPE_SMOKE:channel_count = 1;break;
        case DEVICE_TYPE_LED:channel_count = 1;break;
        case DEVICE_TYPE_LIGHT:channel_count = 1;break;
        default:break;
    }
//更新设备和通道数据
    DEVICE* m_dev = sys_data.dev_map[dev->ID];
    if(NULL == m_dev){
        printf("there have not dev edited\n");
        return;
    }
    memset(m_dev,0,sizeof(DEVICE));
    memcpy(m_dev,dev,sizeof(DEVICE));
//主树上的节点名字修改
    TREEDATA* t_dev = sys_data.tree_devMap[dev->ID];
    if(t_dev==NULL){
        printf("modify dev is not exist\n");
        return;
    }
    wxString xStr(m_dev->name,wxConvUTF8);
    TreeCtrl1->SetItemText(t_dev->ID,xStr);
//设备专有树上的设备节点名字修改
    TREEDATA* tre_dev = sys_data.devTree_map[m_dev->ID];
     if(t_dev==NULL){
        printf("modify dev is not exist\n");
        return;
    }
    TreeCtrl_DevTree->SetItemText(tre_dev->ID,xStr);


    for(int i = 0;i<channel_count;i++){
        DEVICE_CHANNEL* chn = (DEVICE_CHANNEL*)(data+sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL));
        DEVICE_CHANNEL* t_chn = sys_data.devchn_map[chn->ID];
        if(t_chn == NULL){
            printf("edit dev update channel   no such channel node\n");
            continue;
        }
        memset(t_chn,0,sizeof(DEVICE_CHANNEL));
        memcpy(t_chn,chn,sizeof(DEVICE_CHANNEL));
        TREEDATA* tre_chn = sys_data.tree_chnMap[chn->ID];
        if(tre_chn==NULL){
            printf("modify dev is not exist\n");
            return;
        }
        wxString xStr(chn->name,wxConvUTF8);
        TreeCtrl1->SetItemText(tre_chn->ID,xStr);
    }


//更新用户管理设备的数据power_dev
    DEVBELONGUSER* belong = (DEVBELONGUSER*)(data+sizeof(DEVICE)+channel_count*sizeof(DEVICE_CHANNEL));
    printf("belong->num is %d\n",belong->num);
    //取消管理该设备的用户集

    map<int,USERINFO*>::iterator t_ite;
    printf("size cancel_devUserMap is %d\n",cancel_devUserMap.size());
    for(t_ite=cancel_devUserMap.begin();t_ite!=cancel_devUserMap.end();t_ite++){
        USERINFO* usr = t_ite->second;
        char tmp_dev[512] = {0};
        memcpy(tmp_dev,usr->power_dev,512);
        memset(usr->power_dev,0,512);

        char tmp_id[8] = {0};
        sprintf(tmp_id,"%d",dev->ID);
        printf("del power dev num is %s\n",tmp_dev);
        printf("tar str is %s\n",tmp_id);
        char* ret = strstr(tmp_dev,tmp_id);
        char* tok = NULL;
        char* sep = NULL;
        if(ret == NULL)
            continue;
        if(ret != tmp_dev) {//first id is the delete num
            *(ret-1) = 0;
        }
        tok = ret;
        printf("tok is %s\n",tok);
        sep = strtok(tok,",");
        if(tok== NULL)
            sprintf(usr->power_dev,"%s",tmp_dev);
        else
            sprintf(usr->power_dev,"%s,%s",tmp_dev,tok);

    }

    for(int i = 0;i<belong->num;i++){
            printf("belong->usr[%d] is %s\n",i,belong->usr[i]);
        map<int,USERINFO*>::iterator t_ite;
        for(t_ite=sys_data.user_map.begin();t_ite!=sys_data.user_map.end();t_ite++){
            USERINFO* usr = t_ite->second;
            if(strcmp(usr->Name,belong->usr[i]) == 0){
                printf("user_map use\n");
                char devID[8] = {0};
                sprintf(devID,"%d",dev->ID);
                char* ret = strstr(usr->power_dev,devID);
                if(ret == NULL){
                    if(0 != *(usr->power_dev))
                        sprintf((usr->power_dev)+strlen(usr->power_dev),",%d",dev->ID);
                    else
                        sprintf((usr->power_dev)+strlen(usr->power_dev),"%d",dev->ID);
                }
                printf("user_map new power devis \n%s\n",usr->power_dev);
            }
        }

    }
    wxLogMessage("修改设备成功");
}

void New_PowerMangerFrame::SetNewDevOnTree(char* data)
{
    DEVICE* m_dev = new DEVICE;
    memset(m_dev,0,sizeof(DEVICE));
    memcpy(m_dev,data,sizeof(DEVICE));
    int channel_count = 0;
    switch(m_dev->type ){
        case DEVICE_TYPE_HK:channel_count = 4;break;
        case DEVICE_TYPE_GH:channel_count = 0;break;
        case DEVICE_TYPE_HB:channel_count = 16;break;
        case DEVICE_TYPE_DH:channel_count = 0;break;
        case DEVICE_TYPE_JG:channel_count = 0;break;
        case DEVICE_TYPE_WD:channel_count = 0;break;
        case DEVICE_TYPE_DJL:channel_count = 0;break;
        case DEVICE_TYPE_WL:channel_count = 0;break;
        case DEVICE_TYPE_SMOKE:channel_count = 1;break;
        case DEVICE_TYPE_LED:channel_count = 1;break;
        case DEVICE_TYPE_LIGHT:channel_count = 1;break;
        default:break;
    }
    printf("m_dev->name %s\n",m_dev->name);
    printf("channel_count %d\n",channel_count);

//主树上节点加载
    TREEDATA* p_node = sys_data.tree_devGrpMap[m_dev->group_ID];
    if(NULL != p_node){
        TREEDATA* m_data = new TREEDATA;
        memset(m_data,0,sizeof(TREEDATA));
        m_data->flag = TREE_FLAG_DEVICE;
        m_data->data = (char*)m_dev;
        wxString xStr(m_dev->name,wxConvUTF8);
        m_data->ID = TreeCtrl1->AppendItem(p_node->ID,xStr);

        TreeCtrl1->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        sys_data.dev_map[m_dev->ID] = m_dev;
        sys_data.tree_devMap[m_dev->ID] = m_data;
    }
    for(int i = 0;i<channel_count;i++){
        DEVICE_CHANNEL* m_chn = new DEVICE_CHANNEL;
        memset(m_chn,0,sizeof(DEVICE_CHANNEL));
        memcpy(m_chn,data+sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),sizeof(DEVICE_CHANNEL));
        TREEDATA* p_dev = sys_data.tree_devMap[m_chn->group_ID];
        if(p_dev != NULL){
            TREEDATA* m_data = new TREEDATA;
            memset(m_data,0,sizeof(TREEDATA));
            m_data->flag = TREE_FLAG_DEVICECHANNEL;
            m_data->data = (char*)m_chn;
            wxString xStr(m_chn->name,wxConvUTF8);
            m_data->ID = TreeCtrl1->AppendItem(p_dev->ID,xStr);
            TreeCtrl1->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        }
    }

/***************用户界面上的设备树控件上将新节点加入******************/
    TREEDATA* pdev_node = sys_data.devTree_map[m_dev->group_ID];
    if(NULL != pdev_node){
        TREEDATA* m_data = new TREEDATA;
        memset(m_data,0,sizeof(TREEDATA));
        m_data->flag = TREE_FLAG_DEVICE;
        m_data->data = (char*)m_dev;
        wxString xStr(m_dev->name,wxConvUTF8);
        m_data->ID = TreeCtrl_DevTree->AppendItem(pdev_node->ID,xStr);
        TreeCtrl_DevTree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        sys_data.devTree_map[m_dev->ID] = m_data;
    }

/*****************************************
更新在新建设备节点时选择的管理用户，
将现在主树和用户树节点中的用户数据的
设备管理权限更新
****************************************/
    DEVBELONGUSER* belong = (DEVBELONGUSER*)(data+sizeof(DEVICE)+channel_count*sizeof(DEVICE_CHANNEL));
    printf("belong->num is %d\n",belong->num);
    for(int i = 0;i<belong->num;i++){
        map<int,USERINFO*>::iterator t_ite;

        for(t_ite=sys_data.user_map.begin();t_ite!=sys_data.user_map.end();t_ite++){
            USERINFO* usr = t_ite->second;
            if(strcmp(usr->Name,belong->usr[i]) == 0){
                printf("user_map use\n");
                sprintf((usr->power_dev)+strlen(usr->power_dev),",%d",m_dev->ID);
                printf("user_map new power devis \n%s\n",usr->power_dev);
            }
        }

    }
}

void New_PowerMangerFrame::SetNewDevGrpOnTree(char* data)
{
/*************主树控件上将新增设备节点加入************/
    DEVICE_GRP* m_dev_group = new DEVICE_GRP;
    memset(m_dev_group,0,sizeof(DEVICE_GRP));
    memcpy(m_dev_group,data,sizeof(DEVICE_GRP));
    if(m_dev_group->PID == 0){
        wxString xStr(m_dev_group->name,wxConvUTF8);
        TREEDATA* m_data = new TREEDATA;
        memset(m_data,0,sizeof(TREEDATA));
        m_data->flag = TREE_FLAG_DEVICEGROUP;
        m_data->data = (char*)(m_dev_group);
        m_data->ID = TreeCtrl1->AppendItem(GetTreeDeviceParentID(),xStr);

        TreeCtrl1->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        sys_data.devgroup_map[m_dev_group->ID] = m_dev_group;
        sys_data.tree_devGrpMap[m_dev_group->ID] = m_data;
    }
    else{
        TREEDATA* p_grp = sys_data.tree_devGrpMap[m_dev_group->PID];
        if(NULL == p_grp){
            printf("new dev group data error\n");
            return;
        }
        wxString xStr(m_dev_group->name,wxConvUTF8);
        TREEDATA* m_data = new TREEDATA;
        memset(m_data,0,sizeof(TREEDATA));
        m_data->flag = TREE_FLAG_DEVICEGROUP;
        m_data->data = (char*)m_dev_group;
        m_data->ID = TreeCtrl1->AppendItem(p_grp->ID,xStr);

        TreeCtrl1->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        sys_data.devgroup_map[m_dev_group->ID] = m_dev_group;
        sys_data.tree_devGrpMap[m_dev_group->ID] = m_data;
    }

/***************用户界面上的设备树控件上将新节点加入******************/

    if(m_dev_group->PID == 0){
        TREEDATA* m_data = new TREEDATA;
        memset(m_data,0,sizeof(TREEDATA));
        m_data->flag = TREE_FLAG_DEVICEGROUP;
        m_data->data = (char*)m_dev_group;

        wxString xStr(m_dev_group->name,wxConvUTF8);
        m_data->ID = TreeCtrl_DevTree->AppendItem(GetTreeUserDevParentID(),xStr);

        TreeCtrl_DevTree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        TreeCtrl_DevTree->SetItemState(m_data->ID,1);
        sys_data.devgroupTree_map[m_dev_group->ID] = m_data;
    }
    else{
        TREEDATA* p_grp = sys_data.devgroupTree_map[m_dev_group->PID];
        if(NULL == p_grp){
            printf("new dev group data error\n");
            return;
        }
        TREEDATA* m_data = new TREEDATA;
        memset(m_data,0,sizeof(TREEDATA));
        m_data->flag = TREE_FLAG_DEVICEGROUP;
        m_data->data = (char*)m_dev_group;
        wxString xStr(m_dev_group->name,wxConvUTF8);
        m_data->ID = TreeCtrl_DevTree->AppendItem(p_grp->ID,xStr);
        TreeCtrl_DevTree->SetItemState(m_data->ID,1);
        TreeCtrl_DevTree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        sys_data.devgroupTree_map[m_dev_group->ID] = m_data;
    }
}

void New_PowerMangerFrame::SearchAllTreeItemOnItem(wxTreeItemId item,char* power)
{
    if(TreeCtrl_powerManager->ItemHasChildren(item)){
        wxTreeItemIdValue cookie;
        wxTreeItemId t_item;
        t_item = TreeCtrl_powerManager->GetFirstChild(item,cookie);

        while(t_item.IsOk()){
            if(0 == TreeCtrl_powerManager->GetItemState(t_item)){    //有权限
                TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(t_item))->GetData();
                LIMIT info;
                memset(&info,0,sizeof(LIMIT));
                memcpy(&info,(LIMIT*)(node->data),sizeof(LIMIT));
                printf(" have power ID is %d\n",info.ID);
                sprintf(power+strlen(power),"%d,",info.ID);
            }
            t_item = TreeCtrl1->GetNextChild(item,cookie);
        }
    }
    else
        return;
}

void New_PowerMangerFrame::Show_DeviceInfo(DEVICE* dev,wxTreeItemId item)
{
    wxString str_name(dev->name,wxConvUTF8);
    wxString str_sys_num(dev->sys_num,wxConvUTF8);
    wxString str_Model(dev->model,wxConvUTF8);
    wxString str_IP(dev->IP,wxConvUTF8);
    wxString str_port;
    str_port<<dev->port;


    Clear_DevGui();
    Disable_DevGui();
    TextCtrl_DevName->AppendText(str_name);
    TextCtrl_devNum->AppendText(str_sys_num);

    TextCtrl_devModel->AppendText(str_Model);
    TextCtrl_devIP->AppendText(str_IP);
    TextCtrl_devPort->AppendText(str_port);
    switch(dev->type){
        case DEVICE_TYPE_HK:Choice_devType->SetSelection(0);break;       //选中海康
        case DEVICE_TYPE_GH:Choice_devType->SetSelection(1);break;     //选中捷高
        case DEVICE_TYPE_HB:Choice_devType->SetSelection(2);break;     //选中冠辉
        case DEVICE_TYPE_SMOKE:Choice_devType->SetSelection(8);break;
        case DEVICE_TYPE_LED:Choice_devType->SetSelection(9);break;
        case DEVICE_TYPE_LIGHT:Choice_devType->SetSelection(10);break;
        default:
            break;
    }

    /*****显示设备通道************/

    wxTreeItemIdValue cookie;
    wxTreeItemId t_item = TreeCtrl1->GetFirstChild(item,cookie);

    while(t_item.IsOk()){
        DEVICE_CHANNEL chn;
        TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(t_item))->GetData();
        memcpy(&chn,&(((Tree_DeviceChn*)(node->data))->dev_chn),sizeof(DEVICE_CHANNEL));
        wxString chn_name(chn.name,wxConvUTF8);
        wxString chn_status("off",wxConvUTF8);
        wxString str[2] = {chn_name,chn_status};
        wxListItem it;
        ListCtrl_Channel->InsertItem(0,it);
        for(int j = 0;j<2;j++){
            it.SetColumn(j);
            it.SetText(str[j]);
            ListCtrl_Channel->SetItem(it);
        }
        t_item = TreeCtrl1->GetNextChild(item,cookie);
    }
    SetSelectionOnUserTreeOnDevGuiDevUserStatus(dev->ID);   //显示能管理这个设备的用户
}


//show end
//
//set function

void New_PowerMangerFrame::AddNewDev_Func()
{
    if(TextCtrl_devModel->IsEmpty()){
        wxLogWarning(wxT("请输入设备型号"));
        return;
    }
    if(TextCtrl_devNum->IsEmpty()){
        wxLogWarning(wxT("请输入设备统一编码"));
        return;
    }
    if(TextCtrl_devIP->IsEmpty()){
        wxLogWarning(wxT("请输入设备IP"));
        return;
    }
    if(TextCtrl_devPort->IsEmpty()){
        wxLogWarning(wxT("请输入设备端口"));
        return;
    }
    if(wxNOT_FOUND == Choice_devType->GetSelection()){
        wxLogWarning(wxT("请输入选择设备品牌"));
        return;
    }
    int ret = wxMessageBox(wxT("确认增加设备节点"),wxT("确认提示"),wxYES_NO);
    if(ret == wxNO){
        printf("取消增加设备节点\n");
        return ;
    }

    DEVICE dev;
    memset(&dev,0,sizeof(DEVICE));
    int chn_num = 0;
    switch(Choice_devType->GetSelection()){
        case 0:dev.type = DEVICE_TYPE_HK;chn_num = 4;break;
        case 1:dev.type = DEVICE_TYPE_GH;chn_num = 4;break;
        case 2:dev.type = DEVICE_TYPE_HB;chn_num = 16;break;
        case 8:dev.type = DEVICE_TYPE_SMOKE;chn_num = 1;break;
        case 9:dev.type = DEVICE_TYPE_LED;chn_num = 1;break;
        case 10:dev.type = DEVICE_TYPE_LIGHT;chn_num = 1;break;
        default:
            break;
    }

    Ecode_Conv conv;
    string t_model;
    char model[32] = {0};
    memcpy(model,(const char*)(TextCtrl_devModel->GetValue().mb_str()),32);
    conv.GB2312ToUTF_8(t_model,model,32);
    memcpy(dev.model,(char*)t_model.c_str(),strlen((char*)t_model.c_str()));

    string t_name;
    char name[64] = {0};
    memcpy(name,(const char*)(TextCtrl_DevName->GetValue().mb_str()),64);
    conv.GB2312ToUTF_8(t_name,name,64);
    memcpy(dev.name,(char*)t_name.c_str(),strlen((char*)t_name.c_str()));

    string t_sysnum;
    char sysnum[32] = {0};
    memcpy(sysnum,(const char*)(TextCtrl_devNum->GetValue().mb_str()),32);
    conv.GB2312ToUTF_8(t_sysnum,sysnum,64);
    memcpy(dev.sys_num,(char*)t_sysnum.c_str(),strlen((char*)t_sysnum.c_str()));

    memcpy(dev.IP,(const char*)(TextCtrl_devIP->GetValue().mb_str()),strlen((const char*)(TextCtrl_devIP->GetValue().mb_str())));
    dev.port = wxAtoi(TextCtrl_devPort->GetValue());


    if(add_dev_flag == TREE_FLAG_ADDDEV_AT_GRP){        //点击设备组选择的增加设备节点
        dev.group_ID = ((Tree_DeviceGrp*)(new_dev_trance->data))->dev_grp.ID;
    }
    else if(add_dev_flag == TREE_FLAG_ADDDEV_AT_DEV){
        dev.group_ID = ((Tree_Device*)(new_dev_trance->data))->device.group_ID;
    }

    DEVBELONGUSER belong;
    char *buff = new char[sizeof(DEVICE_CHANNEL)*chn_num+sizeof(DEVICE)+sizeof(DEVBELONGUSER)];
    memset(buff,0,sizeof(DEVICE_CHANNEL)*4+sizeof(DEVICE));
    memcpy(buff,&dev,sizeof(DEVICE));
    wxListItem item;

    for(int i = 0;i<chn_num;i++){
        item.m_itemId = i;
        item.m_mask = wxLIST_MASK_TEXT;
        ListCtrl_Channel->GetItem(item);
        wxString str = item.m_text;
       // wxLogWarning(str);

      // GB2312ToUTF_8
        DEVICE_CHANNEL chn;
        memset(&chn,0,sizeof(DEVICE_CHANNEL));
        memcpy(chn.name,(const char*)str.mb_str(),strlen((const char*)str.mb_str()));
        chn.chn_num = i+1;
        string t_chn;
        conv.GB2312ToUTF_8(t_chn,chn.name,64);
        memset(chn.name,0,64);
        memcpy(chn.name,(char*)t_chn.c_str(),strlen((char*)t_chn.c_str()));
       // chn_vect.push_back(chn);
        memcpy(buff+sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),&chn,sizeof(DEVICE_CHANNEL));
    }
    memset(&belong,0,sizeof(DEVBELONGUSER));
    GetSelectionOnUserTreeOnDevGuiDevUserStatus(&belong);
    memcpy(buff+sizeof(DEVICE)+chn_num*sizeof(DEVICE_CHANNEL),&belong,sizeof(DEVBELONGUSER));

    Request_To_MCS(NET_PACKTYPE_MCS_ADDDEVICE,buff,sizeof(DEVICE_CHANNEL)*chn_num+sizeof(DEVICE)+sizeof(DEVBELONGUSER));


    new_dev_trance = NULL;

    Disable_DevGui();
}

void New_PowerMangerFrame::ModifyDev_Func()
{

    if(TextCtrl_devModel->IsEmpty()){
        wxLogWarning(wxT("请输入设备型号"));
        return;
    }
    if(TextCtrl_devNum->IsEmpty()){
        wxLogWarning(wxT("请输入设备统一编码"));
        return;
    }
    if(TextCtrl_devIP->IsEmpty()){
        wxLogWarning(wxT("请输入设备IP"));
        return;
    }
    if(TextCtrl_devPort->IsEmpty()){
        wxLogWarning(wxT("请输入设备端口"));
        return;
    }
    if(wxNOT_FOUND == Choice_devType->GetSelection()){
        wxLogWarning(wxT("请输入选择设备品牌"));
        return;
    }
    int ret = wxMessageBox(wxT("确认修改设备节点"),wxT("确认提示"),wxYES_NO);
    if(ret == wxNO){
        printf("取消修改设备节点\n");
        return ;
    }

    TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(TreeCtrl1->GetSelection()))->GetData();

    DEVICE dev;
    memset(&dev,0,sizeof(DEVICE));
    dev.ID = ((DEVICE*)(node->data))->ID;
    dev.group_ID = ((DEVICE*)(node->data))->group_ID;

    int chn_num = 0;
    switch(Choice_devType->GetSelection()){
        case 0:dev.type = DEVICE_TYPE_HK;chn_num = 4;break;
        case 1:dev.type = DEVICE_TYPE_GH;chn_num = 4;break;
        case 2:dev.type = DEVICE_TYPE_HB;chn_num = 16;break;
        case 8:dev.type = DEVICE_TYPE_SMOKE;chn_num = 1;break;
        case 9:dev.type = DEVICE_TYPE_LED;chn_num = 1;break;
        case 10:dev.type = DEVICE_TYPE_LIGHT;chn_num = 1;break;
        default:
            break;
    }

    Ecode_Conv conv;
    string t_model;
    char model[32] = {0};
    memcpy(model,(const char*)(TextCtrl_devModel->GetValue().mb_str()),32);
    conv.GB2312ToUTF_8(t_model,model,32);
    memcpy(dev.model,(char*)t_model.c_str(),strlen((char*)t_model.c_str()));

    string t_name;
    char name[64] = {0};
    memcpy(name,(const char*)(TextCtrl_DevName->GetValue().mb_str()),64);
    conv.GB2312ToUTF_8(t_name,name,64);
    memcpy(dev.name,(char*)t_name.c_str(),strlen((char*)t_name.c_str()));

    string t_sysnum;
    char sysnum[32] = {0};
    memcpy(sysnum,(const char*)(TextCtrl_devNum->GetValue().mb_str()),32);
    conv.GB2312ToUTF_8(t_sysnum,sysnum,64);
    memcpy(dev.sys_num,(char*)t_sysnum.c_str(),strlen((char*)t_sysnum.c_str()));

    memcpy(dev.IP,(const char*)(TextCtrl_devIP->GetValue().mb_str()),strlen((const char*)(TextCtrl_devIP->GetValue().mb_str())));
    dev.port = wxAtoi(TextCtrl_devPort->GetValue());


    char *buff = new char[sizeof(DEVICE_CHANNEL)*chn_num+sizeof(DEVICE)+sizeof(DEVBELONGUSER)];
    memset(buff,0,sizeof(DEVICE_CHANNEL)*4+sizeof(DEVICE));
    memcpy(buff,&dev,sizeof(DEVICE));



    wxTreeItemIdValue cookie;
    wxTreeItemId sel = node->ID;
    wxTreeItemId itemID = TreeCtrl1->GetFirstChild(sel,cookie);
    wxListItem item;

    for(int i = 0;i<chn_num;i++){
        item.m_itemId = i;
        item.m_mask = wxLIST_MASK_TEXT;
        ListCtrl_Channel->GetItem(item);
        wxString str = item.m_text;

        TREEDATA* c_node = ((MyTreeData *)TreeCtrl1->GetItemData(itemID))->GetData();
        DEVICE_CHANNEL* chn = (DEVICE_CHANNEL*)(c_node->data);
        memset(chn->name,0,64);
        memcpy(chn->name,(const char*)str.mb_str(),strlen((const char*)str.mb_str()));

        string t_chn;
        conv.GB2312ToUTF_8(t_chn,chn->name,64);
        memset(chn->name,0,64);
        memcpy(chn->name,(char*)t_chn.c_str(),strlen((char*)t_chn.c_str()));

        memcpy(buff+sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),chn,sizeof(DEVICE_CHANNEL));
        if(itemID.IsOk())
            itemID = TreeCtrl_User->GetNextChild(sel,cookie);
    }
    DEVBELONGUSER belong;
    memset(&belong,0,sizeof(DEVBELONGUSER));
    GetSelectionOnUserTreeOnDevGuiDevUserStatus(&belong);

    map<int,USERINFO*>::iterator item_cancel;
    int i = 0;
    belong.cn_num = cancel_devUserMap.size();
    for(item_cancel = cancel_devUserMap.begin();item_cancel!=cancel_devUserMap.end();item_cancel++){
        USERINFO* usr = item_cancel->second;
        memcpy(belong.cancel_usr[i],usr->Name,16);
        printf("cancel usr dev name is %s\n",belong.cancel_usr[i]);
        i++;
    }

    memcpy(buff+sizeof(DEVICE)+chn_num*sizeof(DEVICE_CHANNEL),&belong,sizeof(DEVBELONGUSER));

    Request_To_MCS(NET_PACKTYPE_MCS_EDITDEVICE,buff,sizeof(DEVICE_CHANNEL)*chn_num+sizeof(DEVICE)+sizeof(DEVBELONGUSER));
    new_dev_trance = NULL;
    Disable_DevGui();

}


