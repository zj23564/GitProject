#include <iostream>
#include "lcfile.h"
using namespace std;

int main()
{
    LCFile file;
    file.CreateHugeFile("jj");
  //  file.OpenFile_ReadOnly();
   //file.OpenFile_ShareMode();
    //file.OpenFile_ExclusiveMode();

    file.WriteMemFile(0,0,NULL);
   // file.ReadMemFile();
    getchar();
    return 0;
}
