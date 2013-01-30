#ifndef ECODE_CONV_H
#define ECODE_CONV_H
#include <windows.h>
#include <string>
using namespace std;
class Ecode_Conv
{
    public:
        Ecode_Conv();
        virtual ~Ecode_Conv();
        void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode 转换成UTF-8
        void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 转换成　Unicode
        void GB2312ToUTF_8(string& pOut,char *pText, int pLen);//GB2312 转为 UTF-8
    protected:
    private:
};

#endif // ECODE_CONV_H
