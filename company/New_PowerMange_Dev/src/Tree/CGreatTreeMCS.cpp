#include "../../include/Tree/CGreatTree.h"
#include "string.h"
#include <map>
#include <queue>
#include "wx/msgdlg.h"
#include "../../include/define/Define_Page.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include <wx/icon.h>
#include "../checked.xpm"
#include "../unchecked.xpm"
using namespace std;





void CGreatTree::CreatDevTreeRecureOnUserGui(Tree_DeviceGrp* pre)
{
    map<unsigned int, Tree_DeviceGrp*>::iterator iter;
    for(iter = devgroupTree_map.begin();iter != devgroupTree_map.end();){
        Tree_DeviceGrp* second = iter->second;
        if(second->dev_grp.PID == pre->dev_grp.ID){
            wxString xStr1(second->dev_grp.name,wxConvUTF8);
            second->ID = p_Tree->AppendItem(pre->ID,xStr1);

            TREEDATA* m_data = new TREEDATA;
            m_data->flag = TREE_FLAG_DEVICEGROUP;
            m_data->data = (char*)second;
            p_Tree->SetItemState(second->ID,1);
            p_Tree->SetItemData(second->ID,(wxTreeItemData*)new MyTreeData(m_data));
            iter++;
            CreatDevTreeRecureOnUserGui(second);
        }
        else{
        iter++;
        }
    }

}

void CGreatTree::CreatDevTreeOnUserGui()
{
        COUNT cout_node;
        memcpy(&cout_node,allTreeData,sizeof(COUNT));


        Tree_DeviceGrp* m_dev_group = new Tree_DeviceGrp[cout_node.Count_Group];
        Tree_Device* m_dev = new Tree_Device[cout_node.Count_Device];
        Tree_DeviceChn* m_chn = new Tree_DeviceChn[cout_node.Count_Channel];
        int bottom_lev = 1;
        int top_lev = 1;
        for(int i = 0;i<cout_node.Count_Group;i++){
            memcpy(&((m_dev_group+i)->dev_grp),allTreeData+sizeof(COUNT)+i*sizeof(DEVICE_GRP),sizeof(DEVICE_GRP));


            devgroupTree_map[((m_dev_group+i)->dev_grp).ID] = m_dev_group+i;
            if(((m_dev_group+i)->dev_grp).lev == top_lev){      //首层数据
                m_queueTree.push(m_dev_group+i);
            }

            if(bottom_lev<((m_dev_group+i)->dev_grp).lev){
                bottom_lev = ((m_dev_group+i)->dev_grp).lev;
            }

        }

        for(int i = 0;i<cout_node.Count_Device;i++){
            memcpy(&((m_dev+i)->device),allTreeData+sizeof(COUNT)+cout_node.Count_Group*sizeof(DEVICE_GRP)+i*sizeof(DEVICE),sizeof(DEVICE));
            devTree_map[((m_dev+i)->device).ID] = m_dev+i;
        }

        for(int i = 0;i<cout_node.Count_Channel;i++){
            memcpy(&((m_chn+i)->dev_chn),allTreeData+sizeof(COUNT)+cout_node.Count_Group*sizeof(DEVICE_GRP)+cout_node.Count_Device*sizeof(DEVICE)+i*sizeof(DEVICE_CHANNEL),sizeof(DEVICE_CHANNEL));
            devchnTree_map[((m_chn+i)->dev_chn).ID] = m_chn+i;
        }
        wxImageList * list = new wxImageList(12, 12, true);
        wxIcon ico[2];
        ico[0] = wxIcon(checked_xpm);
        ico[1] = wxIcon(unchecked_xpm);
        list->Add(ico[0]);
        list->Add(ico[1]);
        p_Tree->AssignStateImageList(list);
        while(0 != m_queueTree.size()){
            Tree_DeviceGrp* first = m_queueTree.front();
            wxString xStr(first->dev_grp.name,wxConvUTF8);
            first->ID = p_Tree->AppendItem(Tree_item_ID,xStr);
            TREEDATA* m_data = new TREEDATA;
            m_data->flag = TREE_FLAG_DEVICEGROUP;
            m_data->data = (char*)first;
            p_Tree->SetItemState(first->ID,1);
            p_Tree->SetItemData(first->ID,(wxTreeItemData*)new MyTreeData(m_data));
            m_queueTree.pop();
            CreatDevTreeRecureOnUserGui(first);
        }

        for(iter_devTree = devTree_map.begin();iter_devTree != devTree_map.end();iter_devTree++){
            Tree_Device* dev_tmp = iter_devTree->second;
            Tree_DeviceGrp* grp_tmp = devgroupTree_map[dev_tmp->device.group_ID];
            if(grp_tmp !=NULL){
                 wxString xStr(dev_tmp->device.name,wxConvUTF8);
                 dev_tmp->ID = p_Tree->AppendItem(grp_tmp->ID,xStr);
                 TREEDATA* m_data = new TREEDATA;
                 m_data->flag = TREE_FLAG_DEVICE;
                 m_data->data = (char*)dev_tmp;
                 p_Tree->SetItemState(dev_tmp->ID,1);
                 p_Tree->SetItemData(dev_tmp->ID,(wxTreeItemData*)new MyTreeData(m_data));
            }
            else{
                printf("this dev node no parents\n");
            }
        }


        for(iter_devchnTree = devchnTree_map.begin();iter_devchnTree != devchnTree_map.end();iter_devchnTree++){
            Tree_DeviceChn* chn_tmp = iter_devchnTree->second;
            Tree_Device* dev_tmp = devTree_map[chn_tmp->dev_chn.group_ID];
            if(dev_tmp !=NULL){
                 wxString xStr(chn_tmp->dev_chn.name,wxConvUTF8);
                 chn_tmp->ID = p_Tree->AppendItem(dev_tmp->ID,xStr);
                 TREEDATA* m_data = new TREEDATA;
                 m_data->flag = TREE_FLAG_DEVICECHANNEL;
                 m_data->data = (char*)chn_tmp;
                 p_Tree->SetItemState(chn_tmp->ID,1);
                 p_Tree->SetItemData(chn_tmp->ID,(wxTreeItemData*)new MyTreeData(m_data));
            }
            else{
                printf("this channel node no parents\n");
            }
        }
}

void CGreatTree::CreatDevUserTree()
{
        USERCOUNT cout_node;
        memcpy(&cout_node,allTreeData,sizeof(USERCOUNT));
        Tree_User *m_user = new Tree_User[cout_node.Count_User];
        int tmp;
        printf("user count is %d\n",cout_node.Count_User);

        for(int i = 0;i<cout_node.Count_User;i++)
            memcpy(&(m_user+i)->user,allTreeData+sizeof(USERCOUNT)+i*sizeof(USERINFO),sizeof(USERINFO));


        wxImageList * list = new wxImageList(12, 12, true);
        wxIcon ico[2];
        ico[0] = wxIcon(checked_xpm);
        ico[1] = wxIcon(unchecked_xpm);
        list->Add(ico[0]);
        list->Add(ico[1]);
        p_Tree->AssignStateImageList(list);

        for(int i = 0;i<cout_node.Count_User;i++){
            wxString xStr((const char *)(m_user+i)->user.Name,wxConvUTF8);
            if((m_user+i)->user.power_ID != NULL)
                printf("power ID is %s\n",(m_user+i)->user.power_ID);
            (m_user+i)->sel = i;
            (m_user+i)->ID = p_Tree->AppendItem(Tree_item_ID,xStr);
            TREEDATA* m_data = new TREEDATA;
            m_data->flag = TREE_FLAG_USER;
            m_data->data = (char*)(m_user+i);
            p_Tree->SetItemState((m_user+i)->ID,1);
            p_Tree->SetItemData((m_user+i)->ID,(wxTreeItemData*)new MyTreeData(m_data));
            tmp = (m_user+i)->user.ID;
            userTree_map[tmp] = m_user+i;
        }
}



