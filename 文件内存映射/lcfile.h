#ifndef LCFILE_H
#define LCFILE_H
//#define __USE_FILE_OFFSET64
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>


#include <fcntl.h>
#include <unistd.h>
class LCFile
{
    public:
        LCFile();
        virtual ~LCFile();
        bool CreateHugeFile(char* name);	//创建大文件（小文件一样）
        bool OpenFile_ReadOnly();	//只读方式打开文件
        bool OpenFile_ShareMode();	//共享模式打开文件，加上了文件读锁功能
        bool OpenFile_ExclusiveMode();	//加上了文件写锁的功能，读写锁都是记录锁，强制锁应用层不能实现
		/***********************小体会***************************
		通过fcntl加上的文件锁，为记录锁或者建议锁协同锁，非强制锁，
		记录锁为人为协议，遵守即可使用锁的功能，不遵守，亦奈我何
		*********************************************************/
        void* MemFile(off_t offset,long long len);	//文件映射的起始偏移量（从文件的哪里开始映射）,len,映射多大空间


        long long  ReadFile(long long offset,long long len,char* data);	//读文件 offset从文件哪里开始读，len读多长，data，读到什么地方
        long long  WriteFile(long long offset,long long len,char* data);//根据读文件理解参数
		//读文件映射区
		//讲讲：大文件的映射，采取分段映射，根据函数内容，现在已512*pagesize的大小为一块映射区的大小，用完后释放
		//offset为需要从文件的哪里开始读，len读多长，data读到哪里；
		//len如果超过了一个或者多个映射区的大小，则一个一个映射读取完数据
        bool ReadMemFile(long long offset,long long len,char* data);	
		//讲讲：  同读内存映射区
        bool WriteMemFile(long long offset,long long len,char* data);
        int SetFileMode(int fd,int cmd,int type,int whence,off_t start,off_t len);


        bool OpenFile();
    protected:
    private:
        int fd;	//打开的文件描述符
};

#endif // LCFILE_H
