#include "../../include/encode_conv/Ecode_Conv.h"
Ecode_Conv::Ecode_Conv()
{
    //ctor
}

Ecode_Conv::~Ecode_Conv()
{
    //dtor
}


void Ecode_Conv::UnicodeToUTF_8(char* pOut,wchar_t* pText)  //Unicode 转换成UTF-8
{
    // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
    char* pchar = (char *)pText;

    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));

    return;
}

void Ecode_Conv::Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer)// GB2312 转换成　Unicode
{
    MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
    return ;
}
void Ecode_Conv::GB2312ToUTF_8(string& pOut,char *pText, int pLen)//GB2312 转为 UTF-8
{
    char buf[4];
    int nLength = pLen* 3;
    char* rst = new char[nLength];

    memset(buf,0,4);
    memset(rst,0,nLength);

    int i = 0;
    int j = 0;
    while(i < pLen)
    {
            //如果是英文直接复制就可以
            if( *(pText + i) >= 0)
            {
                    rst[j++] = pText[i++];
            }
            else
            {
                    wchar_t pbuffer;
                    Gb2312ToUnicode(&pbuffer,pText+i);

                    UnicodeToUTF_8(buf,&pbuffer);

                    unsigned short int tmp = 0;
                    tmp = rst[j] = buf[0];
                    tmp = rst[j+1] = buf[1];
                    tmp = rst[j+2] = buf[2];

                    j += 3;
                    i += 2;
            }
    }
    rst[j] = '\0';

    //返回结果
    pOut = rst;
    delete []rst;
    return;
}

