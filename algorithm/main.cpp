#include <iostream>
#include "include/MStack.h"
#include <stdio.h>
using namespace std;

int main()
{
    MStack ss(10);

    ss.DataPush("abc");
    ss.DataPush("def");
    ss.DataPush("ghi");
    ss.DataPush("jkl");
    ss.DataPush("mno");
    //ss.Test();
    printf("pop data is %s\n",ss.DataFront());
    ss.DataPop();
    printf("pop data is %s\n",ss.DataFront());
    ss.DataPop();
    printf("pop data is %s\n",ss.DataFront());
    ss.DataPop();


    return 0;
}
