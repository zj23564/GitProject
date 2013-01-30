#include "lcdir.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>
LCdir::LCdir()
{
    //ctor
}

LCdir::~LCdir()
{
    //dtor
}

bool LCdir::CreateDir(char* name)
{
    if(strncmp(name, "/",1) == 0){
        printf("absolutely path\n");
        memset(dirPath,0,NAME_MAX+1);
        strcpy(dirPath,name);
    }
    else{
        return false;
    }
    if(0>mkdir(name,S_IRWXU)){
        printf("create dir <%s> error\n",name);
        printf("errno is %s\n",strerror(errno));
        return false;
    }

    char t_path[NAME_MAX+1];
    memcpy(t_path,dirPath,NAME_MAX+1);
    char* tmp = t_path;
    char* key;

    while((key = strsep(&tmp,"/")) != NULL){
        memset(dir,0,NAME_MAX+1);
        strcpy(dir,key);
    }
    return true;
}

bool LCdir::DeleteDir(char* name)
{
    if(0 != rmdir(name)){
        printf("remove dir error\n");
        return false;
    }
    return true;
}

char* LCdir::GetDirName()
{
    return dir;
}

char* LCdir::GetDirAllPath()
{
    return dirPath;
}

bool LCdir::ReadOnly()
{
    if(0 != chmod(dir,S_IRUSR)){
            printf("mode dir read only error\n");
            return false;
       }
       return true;

}
bool LCdir::ReadWrite()
{
    if(0 != chmod(dir,S_IRWXU)){
            printf("mode dir rw  error\n");
            return false;
       }
       return true;
}

void LCdir::GetSubDirAndFile(char* path)
{
    struct dirent *file = NULL;
    struct stat st;
    DIR* h_dir;
    if(NULL == (h_dir  = opendir(path))){
            printf("open dir <%s> error\n",path);
        return;
    }
    while((file = readdir(h_dir)) != NULL){
        if(strncmp(file->d_name,".",1) == 0){
            continue;
        }
        char buff[255] = {0};
        sprintf(buff,"%s/%s",path,file->d_name);
        if(stat(buff,&st) ==0 ){
            if(S_ISDIR(st.st_mode)){
                 printf("<%s> is a dir\n",file->d_name);
                 string str(file->d_name);
                 subDir.push_back(str);
            }else if(S_ISREG(st.st_mode)){
                printf("<%s> is a general file\n",file->d_name);
                string str(file->d_name);
                subFile.push_back(str);
            }
        }
    }
}


