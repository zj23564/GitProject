#ifndef LCDIR_H
#define LCDIR_H

#include <string>
#include <vector>

using namespace std;
class LCdir
{
    public:
        LCdir();
        virtual ~LCdir();
        bool CreateDir(char* name);	//创建目录   绝对路径
        bool DeleteDir(char* name);//删除目录
        bool ReadOnly();	//将目录该为只读目录
        bool ReadWrite();	//将目录改为读写目录
        char* GetDirAllPath();	//得到目录的路径
        char* GetDirName();	//得到目录名

        void GetSubDirAndFile(char* path);	//搜索path路径下的目录和文件，目录放在subDir容器里面，文件放在subFile容器里面

        vector<string> subDir;
        vector<string> subFile;
    protected:
    private:
        char dirPath[NAME_MAX+1];
        char dir[NAME_MAX+1];




};

#endif // LCDIR_H
