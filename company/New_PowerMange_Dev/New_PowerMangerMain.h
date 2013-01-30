/***************************************************************
 * Name:      New_PowerMangerMain.h
 * Purpose:   Defines Application Frame
 * Author:    zj ()
 * Created:   2012-07-13
 * Copyright: zj ()
 * License:
 **************************************************************/

#ifndef NEW_POWERMANGERMAIN_H
#define NEW_POWERMANGERMAIN_H

//(*Headers(New_PowerMangerFrame)
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)
#include <wx/image.h>
#include <wx/menu.h>
#include <vector>
#include "include/data/Protocol.h"
#include "include/data/Define_Data.h"
#include "include/net/HT_NET_Engine.h"
#include "include/data/sys_data.h"
using namespace std;
class New_PowerMangerFrame: public wxFrame
{
    public:

        New_PowerMangerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~New_PowerMangerFrame();
        SYSDATA sys_data;


        void SetMcsIp(char* ip){memcpy(McsIp,ip,16);}
        void SetMcsPort(int port){McsPort = port;}
        void GuiInit(void);
        void NetInit();
        void ReadLogPic(void);
        void SetTree();
        void SetListCtrl();

        void Request_To_MCS(int mark,char* data,int data_len);

        void Page_AddUser();
        void Page_DelUser();

        void Page_AddDeviceNode();
        void Show_DeviceInfo(DEVICE* dev,wxTreeItemId item);  //显示设备节点信息
        void SetNewDevGrpOnTree(char* data);
        void Set_ChannelList(int num);        //增加设备节点前的清屏工作
        void SetNewDevOnTree(char* data);     //将新建立的设备节点和通道加入到树节点上
        void UpdateDevOnTree(char*data);    //修改设备节点时，服务端返回的数据
        void SetNewDevID(int m_ID){new_dev->device.ID = m_ID;}
        void DelDevNodeFunc(wxTreeItemId ID);

        void AddNewUser();
        void DelUserFunc();
        void ModifyUserFunc();

        void AddNewDev_Func();
        void ModifyDev_Func();

        void Show_UserInfo(USERINFO* info);
        void Show_UserPowerTree(int powerID);   //传入一个权限ID，然后给权限树上用户有的权限画√
        void Show_UserDevPowerTree(int power_dev);
        void SetNewUserOnTree(char* newUser);
        void SetModifyUserOnTree(char* modifyUser);
        void GetSelectionOnDevTreeOnUserGui(wxTreeItemId sid,char* power_dev,int mark);
        void GetSelectionOnUserTreeOnDevGuiDevUserStatus(DEVBELONGUSER* belong);
        void SetSelectionOnUserTreeOnDevGuiDevUserStatus(int devID);
        void SearchAllTreeItemOnItem(wxTreeItemId item,char* power);    //搜索在该节点下所有子节点
        void DevTreeRecureOnUserGui(Tree_DeviceGrp* pre);    //搜寻用户界面上一个节点下所有的子节点，配合勾选状态改变使用
        void SearchAllParentItemOnItem(wxTreeItemId sid);
        void SearchAllChildItemOnItem(wxTreeItemId id,int mark);


        void PowerManager();//权限项目管理  增加删除修改权限项目
        void SetTreeCtrl_powerManager();
        void SetDevTypeChoice();

      //  void Get_Center_Node(MONITOR_CENTER* center){center_node = center;}

        void Clear_DevGui();        //清除设备界面上的信息
        void ClearOnTreeCtrl_DevUserStatus();
        void Enable_DevGui();
        void Disable_DevGui();

        void Clear_UserGui();        //清除用户界面上的信息
        void SetUserDevTreeStatus(wxTreeItemId sid,int mark);    //mark为1 则取消勾选设备树控件，0则勾选
        void Enable_UserGui();
        void Disable_UserGui();

        wxTreeItemId GetTreeDeviceParentID(){return tree_devID;}
        wxTreeItemId GetTreeUserParentID(){return tree_userID;}
        wxTreeItemId GetTreeUserDevParentID(){return tree_userPageDevID;}
        wxTreeItemId GetTreeDevUserParentID(){return tree_devPageUserID;}
        wxTreeItemId GetTreePowerTreeID(){return powerTreeID;}
        wxTreeItemId GetTreeMonitorTreeID(){return MonitorID;}



         wxTreeCtrl* GetTreeCtrl1(){return TreeCtrl1;}
         wxTreeCtrl* GetTreeCtrl_DevTree(){return TreeCtrl_DevTree;}
         wxTreeCtrl* GetTreeCtrl_UserTree(){return TreeCtrl_User;}
         wxTreeCtrl* GetPowerTree(){return TreeCtrl_powerManager;}
         char* Get_NewPowerItem_Name(){return new_power_name;}     //设置新建立权限项目的名字
         conn_t* Get_Connect(){return fd;}


        char* all_Device_Tree;          //所有的设备组织结构数的数据指针，在新建用户完毕时释放数据内存
        char* all_User_Tree;            //所有的用户组织结构数的数据指针，在新建用户完毕时释放数据内存


         static int session;        //网络链接的返回套接口
        // vector<DEVICE_CHANNEL*>    chn_vect;

    private:

        //(*Handlers(New_PowerMangerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPanel1Paint_Show_Log(wxPaintEvent& event);
        void OnPanel1Resize_Refresh_Panel1(wxSizeEvent& event);
        void OnTreeCtrl1SelectionChanged_DisPlay_GUI(wxTreeEvent& event);
        void OnCheckListBox5Toggled(wxCommandEvent& event);
        void OnCheckListBox_SetUser_Station_Power(wxCommandEvent& event);
        void OnCheckListBox6_SetUser_Stream_Power(wxCommandEvent& event);
        void OnCheckListBox7_SetUser_Log_power(wxCommandEvent& event);
        void OnComboBox1Select_Choose_userGroup(wxCommandEvent& event);
        void OnButton1Click_AddUser(wxCommandEvent& event);
        void OnButton3Click_DeleteUser(wxCommandEvent& event);
        void OnTreeCtrl1ItemRightClick(wxTreeEvent& event);
        void OnButton_Change_DevClick(wxCommandEvent& event);
        void OnButton_Update_DeviceInfoClick(wxCommandEvent& event);
        void OnButton_Add_DeviceClick(wxCommandEvent& event);
        void OnButton_DeleteDevClick(wxCommandEvent& event);
        void OnTreeCtrl1EndLabelEdit(wxTreeEvent& event);
        void OnButton5Click_AddPowerItem(wxCommandEvent& event);
        void OnButton_ChangePowerItemClick(wxCommandEvent& event);
        void OnTreeCtrl_powerManagerItemRightClick(wxTreeEvent& event);
        void OnButton_AddPowerItemClick(wxCommandEvent& event);
        void OnButton_ChangePowerItemClick1(wxCommandEvent& event);
        void OnButton_DelPowerItemClick(wxCommandEvent& event);
        void OnButton_AddPowerClassClick(wxCommandEvent& event);
        void OnButton_ChangePowerClassClick(wxCommandEvent& event);
        void OnButton_DelPowerClassClick(wxCommandEvent& event);
        void OnTreeCtrl_powerManagerSelectionChanged(wxTreeEvent& event);
        void OnButton5Click(wxCommandEvent& event);
        void OnChoice_devTypeSelect(wxCommandEvent& event);
        void OnListCtrl_ChannelBeginLabelEdit(wxListEvent& event);
        void OnListCtrl_ChannelEndLabelEdit(wxListEvent& event);
        void OnTreeCtrl_powerManagerBeginDrag(wxTreeEvent& event);
        void OnTreeCtrl_powerManagerSelectionChanging(wxTreeEvent& event);
        void OnButton_SureUserClick(wxCommandEvent& event);
        void OnTreeCtrl1BeginLabelEdit(wxTreeEvent& event);
        //*)
        void OnTreeCtrl_PowerStatusChange(wxTreeEvent& event);
        void OnTreeCtrl_UserDevStatusChange(wxTreeEvent& event);
        void OnTreeCtrl_DevUserStatusChange(wxTreeEvent& event);
        void NewUser(wxCommandEvent& event);
        void NewUserGroup(wxCommandEvent& event);
        void DelUser(wxCommandEvent& event);
        void ModifyUser(wxCommandEvent& event);
        void NewDev(wxCommandEvent& event);
        void ModifyDev(wxCommandEvent& event);
        void DelDev(wxCommandEvent& event);
        void NewDevGrp(wxCommandEvent& event);
        void NewDevChildGrp(wxCommandEvent& event);
        void DelDevGrp(wxCommandEvent& event);

        void AddNewCentor(wxCommandEvent& event);//增加监控中心事件
        void DelCentor(wxCommandEvent& event);//删除监控中心事件


        //(*Identifiers(New_PowerMangerFrame)
        static const long ID_TREECTRL1;
        static const long ID_PANEL1;
        static const long ID_STATICTEXT7;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT8;
        static const long ID_TEXTCTRL4;
        static const long ID_STATICTEXT9;
        static const long ID_TEXTCTRL5;
        static const long ID_BUTTON9;
        static const long ID_BUTTON10;
        static const long ID_BUTTON12;
        static const long ID_TREECTRL4;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_TREECTRL2;
        static const long ID_PANEL3;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT3;
        static const long ID_CHOICE1;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL7;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL8;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL9;
        static const long ID_STATICTEXT11;
        static const long ID_LISTCTRL5;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_TREECTRL3;
        static const long ID_PANEL8;
        static const long ID_NOTEBOOK1;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_NEWUSER;
        static const long ID_MODIFYUSER;
        static const long ID_NEWUSER_GROUP;
        static const long ID_DELUSER;

        static const long ID_NEWDEV;
        static const long ID_MODIFYDEV;
        static const long ID_NEWDEVGRP;
        static const long ID_NEWDEVCHILDGRP;
        static const long ID_SUREADDDEVGRP;     //确认添加设备组事件ID
        static const long ID_DELDEVGRP;     //删除设备分组
        static const long ID_DELDEV;    //删除设备

        static const long ID_NEWCENTER;
        static const long ID_DELCENTER;

        //(*Declarations(New_PowerMangerFrame)
        wxStaticText* StaticText9;
        wxTreeCtrl* TreeCtrl_DevTree;
        wxButton* Button_AddPowerItem;
        wxListCtrl* ListCtrl_Channel;
        wxTextCtrl* TextCtrl_devModel;
        wxTextCtrl* TextCtrl_DevName;
        wxNotebook* Notebook1;
        wxTextCtrl* TextCtrl_UserPwd;
        wxButton* Button_ChangePowerItem;
        wxTextCtrl* TextCtrl_devPort;
        wxStaticText* StaticText2;
        wxTextCtrl* TextCtrl_UserName;
        wxStaticText* StaticText6;
        wxStaticText* StaticText8;
        wxStaticText* StaticText11;
        wxPanel* Panel8;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxTreeCtrl* TreeCtrl_User;
        wxButton* Button_CancelUser;
        wxButton* Button_Sure_Add_Device;
        wxPanel* Panel3;
        wxTextCtrl* TextCtrl_devIP;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxStatusBar* StatusBar1;
        wxButton* Button_DelPowerItem;
        wxTreeCtrl* TreeCtrl1;
        wxTreeCtrl* TreeCtrl_powerManager;
        wxTextCtrl* TextCtrl_UserSurePwd;
        wxTextCtrl* TextCtrl_devNum;
        wxButton* Button_SureUser;
        wxStaticText* StaticText4;
        wxButton* Button_CancelAdd_Dev;
        wxChoice* Choice_devType;
        //*)

        wxImage* haotel;

        wxTreeItemId tree_devID;    //device node的树节点ID
        wxTreeItemId tree_userID;    //用户的树节点ID
        wxTreeItemId tree_groupID;      //用户组的树节点ID
        wxTreeItemId tree_userPageDevID;    //用户界面上的设备树根节点
        wxTreeItemId tree_devPageUserID;//设备界面上的用户树根节点
        wxTreeItemId powerItemID;       //选择到权限树结构上的树项目ID；用完之后设置为不可用
        wxTreeItemId addCenterNodePID;      //在增加监控中心类型节点时选中的当前节点，作为新加的节点的父节点
        wxTreeItemId powerTreeID;
        wxTreeItemId MonitorID;     //监控中心的父节点

        int newUser_PID;        //新用户的组ID，也可以不存在用户组中
        Tree_User* user_new;        //新增用户的信息，包含它所处的树结构中的ID 和用户信息
        vector<int> del_dev_num;
        vector<int> del_dev_grp_num;
        TREEDATA* new_dev_trance;//当前点击的节点信息，与新建的设备或者设备组节点有关
        TREEDATA* new_dev_node;     //新建的设备组或者设备节点树数据
//        wxTreeItemId new_TreeID;
//        DEVICE_GRP new_grp;
        //Tree_DeviceGrp* new_grp;//新建设备组节点的中间过程存储变量. //新建设备组节点时的树节点ID
        Tree_Device* new_dev;       //新建设备节点的中间过程存储变量. //新建设备节点时的树节点ID
        int add_dev_flag;//标志在增加设备节点时的标志，主要区分是点击在设备组中选中的增加设备节点，还是在点击在设备节点上选择的增加设备节点
        int page_count;
        int flag_edit_label;        //触发编辑树节点名称的事件屏蔽内部功能标志,0为屏蔽功能，1为开放功能
        int flag_operator_user;     //1为 增加用户，2为修改用户，用于在点击用户界面上的确定按钮
        int flag_operator_dev;     //1为 增加设备，2为修改设备，用于在点击设备界面上的确定按钮
        char new_power_name[128];       //新增权限项目的名字

     //   MONITOR_CENTER* center_node;      //新建和修改的监控中心类节点的传输变量
        map<int,USERINFO*> cancel_devUserMap;      //修改设备时，取消原来有控制该设备权限的用户的用户权限的用户集合
        conn_t* fd;
        char McsIp[16];
        int McsPort;

        DECLARE_EVENT_TABLE()
};

#endif // NEW_POWERMANGERMAIN_H
