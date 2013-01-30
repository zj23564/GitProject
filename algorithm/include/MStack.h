#ifndef MSTACK_H
#define MSTACK_H

typedef struct _StackData{
    _StackData* pre;
    _StackData* next;
    char* data;
}StackData;

class MStack
{
    public:
        MStack(int num);
        virtual ~MStack();

        void DataPush(char*);   //进栈
        char* DataFront();
        void DataPop();    //出栈
        bool Stack_Clear(); //清空栈
        bool Stack_Empty(); //栈是否为空

        void Test();

    protected:
    private:
        MStack(MStack&);

        StackData* stack_top;
        StackData* stack_bottom; //

};

#endif // MSTACK_H
