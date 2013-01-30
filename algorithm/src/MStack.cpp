#include "../include/MStack.h"
#include <stdio.h>
MStack::MStack(int num)
{
    stack_top = NULL;
    stack_bottom = NULL;
}

MStack::~MStack()
{
    //dtor
}
int n = 1;
void MStack::DataPush(char* data)   //进栈
{
    if((NULL ==stack_bottom) && (NULL == stack_top)){
        stack_bottom = new StackData;
        stack_bottom->data = data;
        stack_bottom->next = NULL;
        stack_bottom->pre = NULL;
        stack_top = stack_bottom;
        printf("first block\n");
        return;
    }

    StackData* tmp = new StackData;
    tmp->data = data;
    tmp->next = NULL;

    stack_top->next = tmp;
    tmp->pre = stack_top;
    stack_top = tmp;
    printf("block  %d push  stack_top is %s\n",n++,stack_top->data);
    return;

}
void MStack::DataPop()    //出栈
{
    if(NULL == stack_top){
        return;
    }

    StackData* tmp = stack_top;

    stack_top = stack_top->pre;
    delete tmp;
}
bool MStack::Stack_Clear() //清空栈
{
    while(stack_top != NULL){
        if(NULL == stack_top){
            return NULL;
        }
        StackData* tmp = stack_top;
        stack_top = stack_top->pre;
        delete  tmp;
    }
}
bool MStack::Stack_Empty() //栈是否为空
{
    if(stack_bottom == stack_top){
        return true;
    }

    return false;
}
char* MStack::DataFront()
{
    if(NULL == stack_top){
    return NULL;
    }
    return stack_top->data;
}
void MStack::Test()
{
    int i = 1;
   while(stack_top != NULL){

        printf("block <%d> data is <%s>\n",i,stack_top->data);
        i++;
        stack_top = stack_top->pre;
   }
}


