/***************************************************************
 * Name:      ObjectFactoy.cpp
 * Purpose:   Code for Application Class
 * Author:    xrg (xrg_1@yhaoo.com)
 * Created:   2011-10-16
 * Copyright: xrg (xrgsunnning.com)
 * License:
 **************************************************************/
#include "../../include/Tree/CGreatTree.h"
#include "string.h"
#include <queue>
#include "wx/msgdlg.h"
#include "../../include/define/Define_Page.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include <wx/icon.h>
#include "../checked.xpm"
#include "../unchecked.xpm"

using namespace std;



CGreatTree::CGreatTree(wxTreeCtrl *tree,wxTreeItemId Tree_devID,int flag):p_Tree(tree)
{
    //NodeNum = num;

    Tree_item_ID = Tree_devID;
    m_flag = flag;
}

CGreatTree::CGreatTree(New_PowerMangerFrame* frame,wxTreeCtrl *tree,wxTreeItemId Tree_devID,int flag):p_Tree(tree)
{
    //NodeNum = num;

    Tree_item_ID = Tree_devID;
    Frame = frame;
    m_flag = flag;

}
CGreatTree::~CGreatTree()
{

}
MyTreeData::~MyTreeData()
{

}

/******************其它服务器所使用的功能函数**********************/
void CGreatTree::PkgRecvData(char* data,COUNT cout_node)
{
    DEVICE_GRP* m_dev_group = new DEVICE_GRP[cout_node.Count_Group];
    DEVICE* m_dev = new DEVICE[cout_node.Count_Device];
    DEVICE_CHANNEL* m_chn = new DEVICE_CHANNEL[cout_node.Count_Channel];
    m_TTdata = new TTREEDATA[cout_node.Count_Group+cout_node.Count_Device+cout_node.Count_Channel];
    int i,j,k;
    for(i = 0;i<cout_node.Count_Group;i++){
        memcpy(m_dev_group+i,data+sizeof(COUNT)+i*sizeof(DEVICE_GRP),sizeof(DEVICE_GRP));
        (m_TTdata+i)->data = (char*)(m_dev_group+i);
        (m_TTdata+i)->flag = TREE_FLAG_DEVICEGROUP;
    }

    for(j = 0;j<cout_node.Count_Device;j++){
        memcpy(m_dev+j,data+sizeof(COUNT)+cout_node.Count_Group*sizeof(DEVICE_GRP)+j*sizeof(DEVICE),sizeof(DEVICE));
        (m_TTdata+j+i)->data = (char*)(m_dev+j);
        (m_TTdata+j+i)->flag = TREE_FLAG_DEVICE;
    }
    for(k = 0;k<cout_node.Count_Channel;k++){
        memcpy(m_chn+k,data+sizeof(COUNT)+i*sizeof(DEVICE_GRP)+j*sizeof(DEVICE)+k*sizeof(DEVICE_CHANNEL),sizeof(DEVICE_CHANNEL));
        (m_TTdata+j+i+k)->data = (char*)(m_chn+k);
        (m_TTdata+j+i+k)->flag = TREE_FLAG_DEVICECHANNEL;
    }
}

int CGreatTree::GetNodeCount(char* data)
{
    COUNT cout_node;
    memcpy(&cout_node,data,sizeof(COUNT));
    PkgRecvData(data,cout_node);
    return cout_node.Count_Group+cout_node.Count_Device+cout_node.Count_Channel;
}
TTREEDATA* CGreatTree::GetPkgData(int dex)
{
    return m_TTdata+dex;
}

/***********************************************************************

*************************************************************************/
/**********************以下是管理服务器配置界面所需要使用到的变量和树形成函数*/


void CGreatTree::CreatDevTreeRecure(TREEDATA* pre)
{
    map<int,DEVICE_GRP*>::iterator iter;
    for(iter = Frame->sys_data.devgroup_map.begin();iter!=Frame->sys_data.devgroup_map.end();){
        DEVICE_GRP* grp = iter->second;
        if(grp->PID == ((DEVICE_GRP*)(pre->data))->ID){
            TREEDATA* m_data = new TREEDATA;
            memset(m_data,0,sizeof(TREEDATA));
            m_data->flag = TREE_FLAG_DEVICEGROUP;
            m_data->data = (char*)grp;

            wxString xStr1(grp->name,wxConvUTF8);
            m_data->ID = p_Tree->AppendItem(pre->ID,xStr1);


            if(m_flag == 1)
                Frame->sys_data.tree_devGrpMap[grp->ID] = m_data;
            else{
                p_Tree->SetItemState(m_data->ID,1);
                Frame->sys_data.devgroupTree_map[grp->ID] = m_data;
            }
            p_Tree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
            iter++;
            CreatDevTreeRecure(m_data);
        }
        else{
            iter++;
        }
    }

}

void CGreatTree::CreatDevTree()
{

    if(m_flag>1){
        wxImageList * list = new wxImageList(12, 12, true);
        wxIcon ico[2];
        ico[0] = wxIcon(checked_xpm);
        ico[1] = wxIcon(unchecked_xpm);
        list->Add(ico[0]);
        list->Add(ico[1]);
        p_Tree->AssignStateImageList(list);
    }

    queue<DEVICE_GRP*> m_queue;
    map<int,DEVICE_GRP*>::iterator item_grp;
    for(item_grp = Frame->sys_data.devgroup_map.begin();item_grp!=Frame->sys_data.devgroup_map.end();item_grp++){
        DEVICE_GRP* grp = item_grp->second;
        if(grp->lev == 1){  //顶层的分组节点，需要这些节点建立设备树的首层节点数据，以后的数据直接按照关联直接挂载上去
            m_queue.push(grp);
        }
    }

    while(0 != m_queue.size()){
        DEVICE_GRP* grp = m_queue.front();
        wxString xStr(grp->name,wxConvUTF8);
        TREEDATA* m_data = new TREEDATA;
        memset(m_data,0,sizeof(TREEDATA));
        m_data->flag = TREE_FLAG_DEVICEGROUP;
        m_data->data = (char*)grp;
        m_data->ID = p_Tree->AppendItem(Tree_item_ID,xStr);
        if(m_flag == 1)
            Frame->sys_data.tree_devGrpMap[grp->ID] = m_data;
        else{
            p_Tree->SetItemState(m_data->ID,1);
            Frame->sys_data.devgroupTree_map[grp->ID] = m_data;
        }
        p_Tree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        m_queue.pop();

        CreatDevTreeRecure(m_data);

    }

    map<int,DEVICE*>::iterator item_dev;
    for(item_dev = Frame->sys_data.dev_map.begin();item_dev!=Frame->sys_data.dev_map.end();item_dev++){
        DEVICE* dev = item_dev->second;
        TREEDATA* grp = NULL;
        if(m_flag == 1)
            grp = Frame->sys_data.tree_devGrpMap[dev->group_ID];
        else
            grp = Frame->sys_data.devgroupTree_map[dev->group_ID];
        if(grp !=NULL){
            TREEDATA* m_data = new TREEDATA;
            m_data->flag = TREE_FLAG_DEVICE;
            m_data->data = (char*)dev;
            wxString xStr(dev->name,wxConvUTF8);
            m_data->ID = p_Tree->AppendItem(grp->ID,xStr);
            if(m_flag == 1)
                Frame->sys_data.tree_devMap[dev->ID] = m_data;
            else{
                p_Tree->SetItemState(m_data->ID,1);
                Frame->sys_data.devTree_map[dev->ID] = m_data;
            }
            p_Tree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        }
        else{
            printf("this dev node no parents\n");
        }
    }

    if(m_flag == 1){    //如果是主树结构，才加载通道节点
        map<int,DEVICE_CHANNEL*>::iterator item_chn;
        for(item_chn = Frame->sys_data.devchn_map.begin();item_chn!=Frame->sys_data.devchn_map.end();item_chn++){
            DEVICE_CHANNEL* chn = item_chn->second;
            TREEDATA* dev = Frame->sys_data.tree_devMap[chn->group_ID];
            if(dev !=NULL){
                wxString xStr(chn->name,wxConvUTF8);
                TREEDATA* m_data = new TREEDATA;
                memset(m_data,0,sizeof(TREEDATA));

                m_data->flag = TREE_FLAG_DEVICECHANNEL;
                m_data->data = (char*)chn;
                m_data->ID = p_Tree->AppendItem(dev->ID,xStr);
                Frame->sys_data.tree_chnMap[chn->ID] = m_data;
                p_Tree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
            }
            else{
                printf("this channel node no parents\n");
            }
        }

    }
    printf("create dev tree successful\n");
}


void CGreatTree::CreatMonitorCenterTree()
{
    printf("in CreatMonitorCenterTree\n");
    map<int,MONITOR_CENTER*>::iterator item_mon;
    for(item_mon = Frame->sys_data.monitor_map.begin();item_mon != Frame->sys_data.monitor_map.end();item_mon++){
        MONITOR_CENTER* m_monitor = item_mon->second;
        if(NULL != m_monitor){
            if(m_monitor->PID == 0){
                TREEDATA* m_data = new TREEDATA;
                m_data->flag = TREE_FLAG_MONITOR_CENTOR;
                m_data->data = (char*)m_monitor;
                wxString xStr(m_monitor->name,wxConvUTF8);
                m_data->ID = p_Tree->AppendItem(Tree_item_ID,xStr);
                p_Tree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
            }
        }
    }
}


void CGreatTree::CreatUserTree()
{
    if(m_flag>1){
        wxImageList * list = new wxImageList(12, 12, true);
        wxIcon ico[2];
        ico[0] = wxIcon(checked_xpm);
        ico[1] = wxIcon(unchecked_xpm);
        list->Add(ico[0]);
        list->Add(ico[1]);
        p_Tree->AssignStateImageList(list);
    }

    map<int,USERINFO*>::iterator item_usr;
    for(item_usr = Frame->sys_data.user_map.begin();item_usr != Frame->sys_data.user_map.end();item_usr++){
        USERINFO* usr = item_usr->second;
        if(NULL != usr){
            TREEDATA* m_data = new TREEDATA;
            memset(m_data,0,sizeof(TREEDATA));
            m_data->flag = TREE_FLAG_USER;
            m_data->data = (char*)usr;
            wxString xStr(usr->Name,wxConvUTF8);
            m_data->ID = p_Tree->AppendItem(Tree_item_ID,xStr);
            p_Tree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
            if(m_flag>1){
                p_Tree->SetItemState(m_data->ID,1);
                Frame->sys_data.userTree_map[usr->ID] = m_data;
            }
        }
    }
}

void CGreatTree::CreatPowerTree()
{

    wxImageList * list = new wxImageList(12, 12, true);
    wxIcon ico[2];
    ico[0] = wxIcon(checked_xpm);
    ico[1] = wxIcon(unchecked_xpm);
    list->Add(ico[0]);
    list->Add(ico[1]);
    p_Tree->AssignStateImageList(list);

    map<int,LIMIT*>::iterator item_power_grp;

    for(item_power_grp = Frame->sys_data.powergrp_map.begin();item_power_grp != Frame->sys_data.powergrp_map.end();item_power_grp++){
        LIMIT* m_power = item_power_grp->second;
        if(m_power!=NULL){
            TREEDATA* m_data = new TREEDATA;
            memset(m_data,0,sizeof(TREEDATA));
            m_data->flag = TREE_FLAG_POWERGRP;
            m_data->data = (char*)m_power;

            wxString xStr(m_power->name,wxConvUTF8);
            m_data->ID = p_Tree->AppendItem(Tree_item_ID,xStr);
            p_Tree->SetItemState(m_data->ID,1);


            Frame->sys_data.tree_limitMap[m_power->ID] = m_data;
            p_Tree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
        }
    }

    map<int,LIMIT*>::iterator item_power_item;

    for(item_power_item = Frame->sys_data.poweritem_map.begin();item_power_item != Frame->sys_data.poweritem_map.end();item_power_item++){
        LIMIT* m_power = item_power_item->second;
        if(NULL!= m_power){
            TREEDATA* p_power= Frame->sys_data.tree_limitMap[m_power->PID];
            if(p_power != NULL){
                TREEDATA* m_data = new TREEDATA;
                memset(m_data,0,sizeof(TREEDATA));
                m_data->flag = TREE_FLAG_POWERITEM;
                m_data->data = (char*)m_power;
                wxString xStr(m_power->name,wxConvUTF8);
                m_data->ID = p_Tree->AppendItem(p_power->ID,xStr);
                p_Tree->SetItemState(m_data->ID,1);
                p_Tree->SetItemData(m_data->ID,(wxTreeItemData*)new MyTreeData(m_data));
                Frame->sys_data.tree_limitMap[m_power->ID] = m_data;
            }
        }
    }
}
