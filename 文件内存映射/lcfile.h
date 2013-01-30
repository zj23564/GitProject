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
        bool CreateHugeFile(char* name);	//�������ļ���С�ļ�һ����
        bool OpenFile_ReadOnly();	//ֻ����ʽ���ļ�
        bool OpenFile_ShareMode();	//����ģʽ���ļ����������ļ���������
        bool OpenFile_ExclusiveMode();	//�������ļ�д���Ĺ��ܣ���д�����Ǽ�¼����ǿ����Ӧ�ò㲻��ʵ��
		/***********************С���***************************
		ͨ��fcntl���ϵ��ļ�����Ϊ��¼�����߽�����Эͬ������ǿ������
		��¼��Ϊ��ΪЭ�飬���ؼ���ʹ�����Ĺ��ܣ������أ������Һ�
		*********************************************************/
        void* MemFile(off_t offset,long long len);	//�ļ�ӳ�����ʼƫ���������ļ������￪ʼӳ�䣩,len,ӳ����ռ�


        long long  ReadFile(long long offset,long long len,char* data);	//���ļ� offset���ļ����￪ʼ����len���೤��data������ʲô�ط�
        long long  WriteFile(long long offset,long long len,char* data);//���ݶ��ļ�������
		//���ļ�ӳ����
		//���������ļ���ӳ�䣬��ȡ�ֶ�ӳ�䣬���ݺ������ݣ�������512*pagesize�Ĵ�СΪһ��ӳ�����Ĵ�С��������ͷ�
		//offsetΪ��Ҫ���ļ������￪ʼ����len���೤��data�������
		//len���������һ�����߶��ӳ�����Ĵ�С����һ��һ��ӳ���ȡ������
        bool ReadMemFile(long long offset,long long len,char* data);	
		//������  ͬ���ڴ�ӳ����
        bool WriteMemFile(long long offset,long long len,char* data);
        int SetFileMode(int fd,int cmd,int type,int whence,off_t start,off_t len);


        bool OpenFile();
    protected:
    private:
        int fd;	//�򿪵��ļ�������
};

#endif // LCFILE_H
