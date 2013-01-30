

#include "lcfile.h"

LCFile::LCFile()
{
    //ctor
}

LCFile::~LCFile()
{
    //dtor
}

//加文件记录锁
int LCFile::SetFileMode(int fd,int cmd,int type,int whence,off_t start,off_t len)
{
    struct flock lock;
    lock.l_len = len;
    lock.l_start = start;
    lock.l_type = type;
    lock.l_whence = whence;
    return (fcntl(fd,cmd,&lock));
}
//打开文件
bool LCFile::OpenFile()
{
    fd = open("file",O_RDWR);
    if(fd<0){
        printf("%s\n",strerror(errno));
        return false;
    }
}

bool LCFile::CreateHugeFile(char* name)
{

    int stat = system("dd if=/dev/zero of=file bs=1024 count=1");
    if(stat<0){
        printf("system error\n");
        return false;
    }
    printf("system successful\n");
    return true;

}

bool LCFile::OpenFile_ReadOnly()
{
  //  fd = open("test",O_RDONLY);


    fd = open("file",O_RDWR);
    if(fd<0){
        printf("%s\n",strerror(errno));
        return false;
    }
    struct stat st;
    stat("file",&st);
    printf("file size is %lld\n",st.st_size);

    lseek(fd,st.st_size-8,SEEK_SET);


    if(write(fd,"hjkjckd",8)<0){
            perror("write error  \n");
    }

}

bool LCFile::OpenFile_ShareMode()
{
    OpenFile();
    if(SetFileMode(fd,F_SETLK,F_RDLCK,SEEK_SET,0,0)<0){
        printf("set share mode error\n");
    }
}

bool LCFile::OpenFile_ExclusiveMode()
{
    OpenFile();
    if(SetFileMode(fd,F_SETLK,F_WRLCK,SEEK_SET,0,0)<0){
        printf("set exclusive mode error\n");
    }
}

//offset映射文件的起始位置，由计算得到的值传入
void* LCFile::MemFile(off_t offset,long long len)
{
    int block = 512*sysconf(_SC_PAGE_SIZE);
    void* ret = mmap ( 0,block, PROT_READ|PROT_WRITE ,MAP_SHARED, fd, offset);
    if(ret == MAP_FAILED){
        perror("map mem error\n");
        return NULL;
    }
    return ret;
}

bool LCFile::ReadMemFile(long long offset,long long len,char* data)
{
     OpenFile();

    struct stat st;
    stat("file",&st);

    if((st.st_size - offset)< len){
        printf("write beyond memory\n");
        return false;
    }

  //  一块映射区的大小 512倍页的大小
    int block = 512*sysconf(_SC_PAGE_SIZE);

    int mem_count;

//write len data 统计出一共需要映射多少次
    if(len%block == 0){
        mem_count = len/block;
    }
    else{
        mem_count = len/block+1;
    }

    void* addr = NULL;
    for(int i = 0;i<mem_count;i++){

         addr = MemFile((off_t)block*i+offset,block);
        if(addr == MAP_FAILED){
            perror("mem map failed\n");
            return false;
        }

        char* s_addr = (char*)(addr);
        char out[4096*512] = {0};
        memcpy(out,s_addr,block);

        if(msync((void*)s_addr,block,MS_ASYNC) != 0){
            perror("sync error\n");
        }

        if(munmap( addr,block)!= 0){
            perror("munmap error\n");
        }

    }

    close(fd);
    return true;
}


bool LCFile::WriteMemFile(long long offset,long long len,char* data)
{
    OpenFile();

    struct stat st;
    stat("file",&st);

    if((st.st_size - offset)< len){
        printf("write beyond memory\n");
        return false;
    }

  //  一块映射区的大小 512倍页的大小
    int block = 512*sysconf(_SC_PAGE_SIZE);

    int mem_count;

//write len data 统计出一共需要映射多少次
    if(len%block == 0){
        mem_count = len/block;
    }
    else{
        mem_count = len/block+1;
    }

    void* addr = NULL;
    for(int i = 0;i<mem_count;i++){

         addr = MemFile((off_t)block*i+offset,block);
        if(addr == MAP_FAILED){
            perror("mem map failed\n");
            return false;
        }

        char* s_addr = (char*)(addr);

        memcpy(s_addr,data+i*block,block);

        if(msync((void*)s_addr,block,MS_ASYNC) != 0){
            perror("sync error\n");
        }

        if(munmap( addr,block)!= 0){
            perror("munmap error\n");
        }

    }

    close(fd);
    return true;

}

long long  LCFile::ReadFile(long long offset,long long len,char* data)
{
        OpenFile();
        lseek(fd,offset,SEEK_SET);
        long long ret = read(fd,data,len);
        if(ret < 0){
            return  -1;
        }

        return ret;
}
long long  LCFile::WriteFile(long long offset,long long len,char* data)
{
        OpenFile();
        lseek(fd,offset,SEEK_SET);
        long long ret = write(fd,data,len);
        if(ret <0){
            return -1;
        }
        return ret;

}



















