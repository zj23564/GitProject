

#include <stdio.h>
#include "../../include/init/sort.h"
#include "mysql/mysql.h"
#include <string.h>
#include <stdlib.h>
#include "../../include/define/Define.h"

extern MYSQL mysql;

MY_SORT::MY_SORT()
{

    num = NULL;
}

MY_SORT::~MY_SORT()
{

}


void MY_SORT::Node_Class()
{

	}

NODE* MY_SORT::Node_Tree(NODE* first,NODE* second)
{

}

//void MY_SORT::Node_Insert()
//{
//
//
//	}

NODE* MY_SORT::Node_Line()
{

}

//void MY_SORT::Node_Delete()
//{
//
//	}

void MY_SORT::NodeInit()
{
    num = new COUNT;
    mysql_query(&mysql,"select * from dev_group;");
    MYSQL_RES *p = mysql_store_result(&mysql);
    int rowcount = mysql_num_rows(p);
    num->Count_Group = rowcount;
    MYSQL_ROW row = mysql_fetch_row(p);
    for(int i = 0;i<rowcount;i++){


    }


}

void MY_SORT::Node_Insert(NODE* insert)
{

}

