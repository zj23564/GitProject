#ifndef CGREATTREE_H_INCLUDED
#define CGREATTREE_H_INCLUDED
#include "../data/Protocol.h"
#include "../data/Define_Data.h"
#include "../../New_PowerMangerMain.h"

#define TYPE_NODE_DEVICE 0x00000001
#define TYPE_NODE_LINE      0x00000002
#define TYPE_NODE_GROUP   0x00000003
#define TYPE_NODE_COMPANY 0x00000004
//注意，下面这个数据结构只针对主控台
typedef struct _TTREEDATA{
    int flag;           //标志节点是什么节点  用户  设备  设备组 用户组
    char* data;
}TTREEDATA;



class CGreatTree
{
    public :
      CGreatTree(wxTreeCtrl *tree,wxTreeItemId Tree_devID,int flag);
      CGreatTree(New_PowerMangerFrame* frame,wxTreeCtrl *tree,wxTreeItemId Tree_devID,int flag);
      ~CGreatTree();
      void CreatUserTree();
      void CreatDevTree();
      void CreatDevTreeOnUserGui();
      void CreatPowerTree();
      void CreatMonitorCenterTree();
      /******************************************/
      //主控台需要用到的函数
      int GetNodeCount(char* data);
      void PkgRecvData(char* data,COUNT count_node);
      TTREEDATA* GetPkgData(int dex);

      /******************************************/
      void AddTreeNode();
      void DeleteTreeNode();
      void CreatDevTreeRecure(TREEDATA* pre);
      void CreatDevTreeRecureOnUserGui(Tree_DeviceGrp* pre);

      void CreatDevUserTree();

      MCSTREENODE *GetNodeUseNodeName() const;
    void AddTree();

    private:
    wxTreeCtrl *p_Tree;
    int NodeNum;
    char *allTreeData;
/******************主控台使用到的数据*************/
    TTREEDATA*  m_TTdata;

/*************************************/
    New_PowerMangerFrame* Frame;
    wxTreeItemId Tree_item_ID;
    int m_flag;     //1 主树上加载节点，2用户树或者设备树上加载节点

};



class MyTreeData:public wxTreeItemData
{
    public:
        MyTreeData(int data){Treedata = data;}
        MyTreeData(TREEDATA* data){dataTree = data;}
       // MyTreeData(USERGROUP data){UserGroup = data;}
//        MyTreeData(Tree_User data){UserInfo = data;}
//
//        MyTreeData(Tree_Device data){Node = data;}
//        Tree_User Get_UserNode(void){return UserInfo;}
//
//
//        Tree_Device Get_Device(void){return Node;}
        //DEVICE Get_Node(void){return Node;}
        TREEDATA* GetData(void){return dataTree;}
        ~MyTreeData();
    private:
//        Tree_Device TreeCom;
//        Tree_Device TreeGroup;
//        Tree_Device TreeLine;
//        Tree_Device TreeDevice;
//
//        Tree_Device Node;
//        Tree_User UserInfo;

        TREEDATA* dataTree;

        int Treedata;
};






#endif // CGREATTREE_H_INCLUDED
