#include "../../New_PowerMangerMain.h"

#include "../../include/Tree/CGreatTree.h"

#include "../../include/define/Define_Page.h"
#include "../../include/data/Define_Data.h"
#include "../../include/define/Define.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include <wx/icon.h>
#include "../checked.xpm"
#include "../unchecked.xpm"
#include <map>
#include <wx/log.h>
extern New_PowerMangerFrame* Frame;


void New_PowerMangerFrame::Page_AddUser()
{

    Notebook1->SetSelection(1);
}


void New_PowerMangerFrame::AddNewUser()
{
    USERINFO usr_info;
    memset(&usr_info,0,sizeof(USERINFO));
    char passwd[16] = {0};
    memcpy(usr_info.Name,(const char*)(TextCtrl_UserName->GetValue().mb_str()),strlen((const char*)(TextCtrl_UserName->GetValue().mb_str())));
    if(16<strlen((const char*)(TextCtrl_UserPwd->GetValue().mb_str()))){
        wxLogWarning(wxT("密码超过16位"));
        return;
    }
    memcpy(passwd,(const char*)(TextCtrl_UserPwd->GetValue().mb_str()),strlen((const char*)(TextCtrl_UserPwd->GetValue().mb_str())));
    if(0 != strcmp(passwd,(const char*)(TextCtrl_UserSurePwd->GetValue().mb_str()))){
        wxLogWarning(wxT("两次输入密码不相同"));
        return;
    }
    memcpy(usr_info.PassWord,passwd,16);
/***************取权限***********/
    char power[512] = {0};
    wxTreeItemIdValue cookie;
    wxTreeItemId t_item = TreeCtrl_powerManager->GetRootItem();
    t_item = TreeCtrl_powerManager->GetFirstChild(t_item,cookie);

    while(t_item.IsOk()){
        if(0 == TreeCtrl_powerManager->GetItemState(t_item)){    //有权限
            TREEDATA* node = ((MyTreeData *)TreeCtrl_powerManager->GetItemData(t_item))->GetData();
            LIMIT info;
            memset(&info,0,sizeof(LIMIT));
            memcpy(&info,(LIMIT*)(node->data),sizeof(LIMIT));
            sprintf(power+strlen(power),"%d,",info.ID);
            SearchAllTreeItemOnItem(t_item,power);
        }
        else{
            SearchAllTreeItemOnItem(t_item,power);
        }
        t_item = TreeCtrl_powerManager->GetNextChild(t_item,cookie);
    }

    *(power+strlen(power)-1) = '\0';
    printf("all power is \n%s\n",power);
    /******取完权限**************/
    memcpy(usr_info.power_ID,power,512);
    //取用户能控制的设备节点
    int mark = 0;
    wxTreeItemId root = TreeCtrl_DevTree->GetRootItem();
    GetSelectionOnDevTreeOnUserGui(root,usr_info.power_dev,mark);
    *(usr_info.power_dev+strlen(usr_info.power_dev)-1) = '\0';
    printf("mark is %d  user dev is %s  \n",mark,usr_info.power_dev);
    Request_To_MCS(NET_PACKTYPE_MCS_ADDUSER,(char*)(&usr_info),sizeof(USERINFO));

    Disable_UserGui();  //将窗口中控件置为不能使用；
}


void New_PowerMangerFrame::SetNewUserOnTree(char* newUser)
{
/************新用户在主树上的数据挂载*************/
    USERINFO* user_new = new USERINFO;
    memset(user_new,0,sizeof(USERINFO));
    memcpy(user_new,newUser,sizeof(USERINFO));
    TREEDATA* m_data = new TREEDATA;
    m_data->flag = TREE_FLAG_USER;
    m_data->data = (char*)user_new;
    wxString xStr(user_new->Name,wxConvUTF8);
    m_data->ID = TreeCtrl1->AppendItem(GetTreeUserParentID(),xStr);

    TreeCtrl1->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
    int id = user_new->ID;
    sys_data.user_map[id] = user_new;
/************新用户在设备界面信息界面上的用户树数据挂载*************/

    TREEDATA* m_userdata = new TREEDATA;
    memset(m_userdata,0,sizeof(TREEDATA));
    m_userdata->flag = TREE_FLAG_USER;
    m_userdata->data = (char*)user_new;
    wxString Str(user_new->Name,wxConvUTF8);
    m_userdata->ID = TreeCtrl_User->AppendItem(GetTreeDevUserParentID(),Str);
    TreeCtrl_User->SetItemData(m_userdata->ID,(wxTreeItemData*)new MyTreeData(m_userdata));
}

void New_PowerMangerFrame::SetModifyUserOnTree(char* modifyUser)
{
    printf("SetModifyUserOnTree\n");
    USERINFO* usr = (USERINFO*)modifyUser;
    printf("modify user powerID is %s\n",usr->power_ID);
    USERINFO* usrTree = sys_data.user_map[usr->ID];
    if(NULL == usrTree){
        wxLogWarning(wxT("找不到修改后用户"));
        return;
    }
    memset(usrTree->PassWord,0,16);
    memset(usrTree->power_ID,0,512);
    memcpy(usrTree->PassWord,usr->PassWord,16);
    memcpy(usrTree->power_ID,usr->power_ID,512);
    memcpy(usrTree->power_dev,usr->power_dev,512);
    wxLogWarning(wxT("用户修改成功"));
}

void New_PowerMangerFrame::Show_UserInfo(USERINFO* info)    //显示用户信息到界面上
{
    Clear_UserGui();
    wxString str_name(info->Name,wxConvUTF8);
    wxString str_pwd(info->PassWord,wxConvUTF8);
    TextCtrl_UserName->AppendText(str_name);
    TextCtrl_UserPwd->AppendText(str_pwd);
    printf("powe ID is %s\n",info->power_ID);
    printf("powe dev is %s\n",info->power_dev);
    char tmp_ID[512] = {0};
    if(info->power_ID!=NULL){
        memcpy(tmp_ID,info->power_ID,512);
        char *tokenPtr=strtok(tmp_ID,",");
        while(tokenPtr!=NULL)
        {
            printf("%d\n",atoi(tokenPtr));
            Show_UserPowerTree(atoi(tokenPtr));
            tokenPtr=strtok(NULL,",");
        }
    }
    memset(tmp_ID,0,512);

    if(info->power_dev!=NULL){
        memcpy(tmp_ID,info->power_dev,512);
        char *tokenPtr=strtok(tmp_ID,",");
        while(tokenPtr!=NULL)
        {
            printf("user dev power id >>  %d\n",atoi(tokenPtr));
            Show_UserDevPowerTree(atoi(tokenPtr));
            tokenPtr=strtok(NULL,",");
        }
    }

    Disable_UserGui();
}

void New_PowerMangerFrame::Show_UserDevPowerTree(int power_dev)
{

    if(power_dev<9999){
        TREEDATA* grp = sys_data.devgroupTree_map[power_dev];
        if(NULL != grp){
            TreeCtrl_DevTree->SetItemState(grp->ID,0);
            return;
        }
        else{
            printf("no such device group id is %d\n",power_dev);
            return;
        }
    }
    else if((100000>power_dev)&&(power_dev>10000)){
        TREEDATA* dev = sys_data.devTree_map[power_dev];
        if(NULL != dev){
            TreeCtrl_DevTree->SetItemState(dev->ID,0);
            return;
        }
        else{
            printf("no such device id is %d\n",power_dev);
            return;
        }
    }
}

void New_PowerMangerFrame::Show_UserPowerTree(int powerID)      //显示用户权限树
{
    TREEDATA* m_power = sys_data.tree_limitMap[powerID];

    if( m_power != NULL){ //如果有权限ID  证明有权限 树上打勾
        if(((LIMIT*)(m_power->data))->type = 1){       //说明这个权限节点是一个权限项目组，所以它节点之下的节点将全部打勾
            TreeCtrl_powerManager->SetItemState(m_power->ID,0);
            wxTreeItemIdValue cookie;
            wxTreeItemId itemID = TreeCtrl_powerManager->GetFirstChild(m_power->ID,cookie);
            if(itemID.IsOk())
                TreeCtrl_powerManager->SetItemState(itemID,0);
            while(itemID.IsOk()){
                itemID = TreeCtrl_powerManager->GetNextChild(m_power->ID,cookie);
                if(itemID.IsOk())
                    TreeCtrl_powerManager->SetItemState(itemID,0);
                else
                    break;
            }
        }
        else
            TreeCtrl_powerManager->SetItemState(m_power->ID,0);
    }
}

void New_PowerMangerFrame::ModifyUserFunc()
{
    TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(TreeCtrl1->GetSelection()))->GetData();
    USERINFO* usr = (USERINFO*)(node->data);

    USERINFO usr_info;
    memset(&usr_info,0,sizeof(USERINFO));
    usr_info.ID = usr->ID;
    char passwd[16] = {0};
    memcpy(usr_info.Name,(const char*)(TextCtrl_UserName->GetValue().mb_str()),strlen((const char*)(TextCtrl_UserName->GetValue().mb_str())));
    if(16<strlen((const char*)(TextCtrl_UserPwd->GetValue().mb_str()))){
        wxLogWarning(wxT("密码超过16位"));
        return;
    }
    memcpy(passwd,(const char*)(TextCtrl_UserPwd->GetValue().mb_str()),strlen((const char*)(TextCtrl_UserPwd->GetValue().mb_str())));
    if(0 != strcmp(passwd,(const char*)(TextCtrl_UserSurePwd->GetValue().mb_str()))){
        wxLogWarning(wxT("两次输入密码不相同"));
        return;
    }
    memcpy(usr_info.PassWord,passwd,16);
/***************取权限***********/
    char power[512] = {0};
    wxTreeItemIdValue cookie;
    wxTreeItemId t_item = TreeCtrl_powerManager->GetRootItem();
    t_item = TreeCtrl_powerManager->GetFirstChild(t_item,cookie);

    while(t_item.IsOk()){
        if(0 == TreeCtrl_powerManager->GetItemState(t_item)){    //有权限
            TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(t_item))->GetData();
            LIMIT info;
            memset(&info,0,sizeof(LIMIT));
            memcpy(&info,&(((Tree_Power*)(node->data))->power),sizeof(LIMIT));
            sprintf(power+strlen(power),"%d,",info.ID);
            SearchAllTreeItemOnItem(t_item,power);
        }
        else{
            SearchAllTreeItemOnItem(t_item,power);
        }
        t_item = TreeCtrl1->GetNextChild(t_item,cookie);
    }

    *(power+strlen(power)-1) = '\0';
    printf("all power is \n%s\n",power);
    /******取完权限**************/
    memcpy(usr_info.power_ID,power,512);

    //取用户能控制的设备节点
    int mark = 0;
    wxTreeItemId root = TreeCtrl_DevTree->GetRootItem();
    GetSelectionOnDevTreeOnUserGui(root,usr_info.power_dev,mark);
    *(usr_info.power_dev+strlen(usr_info.power_dev)-1) = '\0';
    printf("mark is %d  user dev is %s  \n",mark,usr_info.power_dev);
    Request_To_MCS(NET_PACKTYPE_MCS_EDITUSER,(char*)(&usr_info),sizeof(USERINFO));
    Disable_UserGui();  //讲窗口中控件置为不能使用；

}

void New_PowerMangerFrame::DelUserFunc()
{
    TREEDATA* node = ((MyTreeData *)TreeCtrl1->GetItemData(TreeCtrl1->GetSelection()))->GetData();
    USERINFO* usr = (USERINFO*)(node->data);
    printf("del user name is %s\n",usr->Name);
    Request_To_MCS(NET_PACKTYPE_MCS_DELETEUSER,(char*)usr,sizeof(USERINFO));
    TreeCtrl1->Delete(node->ID);
    sys_data.user_map.erase(usr->ID);
}

void New_PowerMangerFrame::SetSelectionOnUserTreeOnDevGuiDevUserStatus(int devID) //显示能管理ID=devID的设备的用户
{
    char tmp_ID[512] = {0};
    map<int,TREEDATA*>::iterator itTree;
   for(itTree=sys_data.userTree_map.begin();itTree!=sys_data.userTree_map.end();itTree++){
        TREEDATA* user = itTree->second;
        memcpy(tmp_ID,((USERINFO*)(user->data))->power_dev,512);
        char* tokenPtr=strtok(tmp_ID,",");
        while(tokenPtr!=NULL){
            if(devID == atoi(tokenPtr)){
                TreeCtrl_User->SetItemState(user->ID,0);
                break;
            }
            tokenPtr=strtok(NULL,",");
        }
        *tmp_ID = '\0';
    }
}







