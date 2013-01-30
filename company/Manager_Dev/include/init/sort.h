#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "../data_define/Data_Define.h"


class MY_SORT{

	public:
		MY_SORT();
		~MY_SORT();

		void Node_Class();

		NODE* Node_Tree(NODE*,NODE*);   //链表两两合一

		void Node_Insert(NODE* insert/*,map<int,NODE*>& Device_map*/);

		void Node_Delete(NODE* del);
		NODE* Node_Line();       //将不同链表数据连成一个链表
		void NodeInit();        //初始化链表数据，并将链表分类
		COUNT* Get_Count(){return num;}

	private:
        NODE* node_devGroup;
        NODE* node_dev;
        COUNT* num;
	};


#endif // SORT_H_INCLUDED
