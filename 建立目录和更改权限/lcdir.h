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
        bool CreateDir(char* name);	//����Ŀ¼   ����·��
        bool DeleteDir(char* name);//ɾ��Ŀ¼
        bool ReadOnly();	//��Ŀ¼��Ϊֻ��Ŀ¼
        bool ReadWrite();	//��Ŀ¼��Ϊ��дĿ¼
        char* GetDirAllPath();	//�õ�Ŀ¼��·��
        char* GetDirName();	//�õ�Ŀ¼��

        void GetSubDirAndFile(char* path);	//����path·���µ�Ŀ¼���ļ���Ŀ¼����subDir�������棬�ļ�����subFile��������

        vector<string> subDir;
        vector<string> subFile;
    protected:
    private:
        char dirPath[NAME_MAX+1];
        char dir[NAME_MAX+1];




};

#endif // LCDIR_H
