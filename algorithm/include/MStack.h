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

        void DataPush(char*);   //��ջ
        char* DataFront();
        void DataPop();    //��ջ
        bool Stack_Clear(); //���ջ
        bool Stack_Empty(); //ջ�Ƿ�Ϊ��

        void Test();

    protected:
    private:
        MStack(MStack&);

        StackData* stack_top;
        StackData* stack_bottom; //

};

#endif // MSTACK_H
