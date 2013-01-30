#include "../include/Xepoll_Client.h"
#include<libxml/parser.h>
#include<libxml/tree.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char read_buff1[1024]={0};
char read_buff2[1024]={0};
char read_buff3[1024]={0};
char read_buff4[1024]={0};
char timebuff[1024]={0};
char write_buff[512] = {0};

map<int,DEVICE*> Xepoll_Client::Login_device;
//map<int,DEVICE*>Xepoll_Client:: ::iterator iter_login;

void ReadXml()
{
       int sfd;
      sfd=open("xml.xml",O_RDWR);
      if(sfd<0){
        printf("open sound  1\n");
        //exit(EXIT_FAILURE);
        return;
      }
      read(sfd,read_buff1,1024);
      close(sfd);

      sfd=open("request.xml",O_RDWR);
      if(sfd<0){
        printf("open sound  2\n");
        //exit(EXIT_FAILURE);
        return;
      }
      read(sfd,read_buff2,1024);
      //close(sfd);

      sfd=open("request2.xml",O_RDWR);
      if(sfd<0){
        printf("open sound  3\n");
        //exit(EXIT_FAILURE);
        return;
      }
      read(sfd,read_buff3,1024);
      //close(sfd);

}

Xepoll_Client::Xepoll_Client(int Sockfd)
{
	//ctor
	m_Sockfd = Sockfd;
}

Xepoll_Client::~Xepoll_Client()
{
	//dtor
}

int Xepoll_Client::Send(char *Buffer,int Len)
{
	write(this->m_Sockfd,Buffer,Len);

	return this->m_Sockfd;
}

int Xepoll_Client::Recv(char *Buffer,int Size)
{
	read(this->m_Sockfd,Buffer,Size);
	return this->m_Sockfd;
}

void Xepoll_Client::Gettime(void)
{
        time_t tim;
        struct tm * nowtime;
        time(&tim);
        nowtime = localtime(&tim);

        int year = nowtime->tm_year+1900;
        int mon = nowtime->tm_mon+1;
        int day = nowtime->tm_mday;
        int hour = nowtime->tm_hour;
        int min = nowtime->tm_min;
        int sec = nowtime->tm_sec;

        char tmpbuf[512] = {0};
        sprintf(tmpbuf,"%d%02d%02d%02d%02d%02d",year,mon,day,hour,min,sec);
        sprintf(timebuff,"<iq type='set'>\n  <query xmlns='posacar:signaling:heartbeat'>\n    <time>%s</time>\n  </query>\n</iq>",tmpbuf);
}


int register_count = 0;

int Xepoll_Client::Xml_Ans(char* buff,int fd)
{
        xmlDocPtr doc;
        xmlNodePtr root,node,res;
        xmlChar *rt,*id,*passwd,*type,*ns;
   //     int fd = 0;;
       // printf("in ans_xml buff i s\n %s\n ",buff);
  //      xmlNodePtr root,node;
        //xmlChar *rt,*result,*addr,*port,*ns;
        doc = xmlParseMemory(buff,strlen(buff));
        if(doc == NULL){
                printf("file is NULL\n");
                return 0;
        }
        root = xmlDocGetRootElement(doc);
        for(node = root->children;node;node = node->next){
                //printf("node name is\n%s\n",node->name);
                if(xmlStrcasecmp(node->name,BAD_CAST"query")==0){
                  //      printf("xmlns is  %s\n",node->ns->href);
                        char* p = strtok((char*)(node->ns->href),":");
                        p=strtok(NULL,":");
                        p=strtok(NULL,":");
                        printf("p is %s\n",p);

                        if(0==strcmp(p,"querylb")){
                        	printf("device serch\n");

/*************解析出设备的ID 和密码 还有类型*****************/
							memcpy(write_buff,read_buff1,strlen(read_buff1));
							printf("write buff is \n%s\n ",write_buff);
							fd = Send(write_buff,strlen(write_buff));
							memset(write_buff,0,512);
							break;
                        }
                        else if(0==strcmp(p,"register")){
                        	printf("device register\n");
                        	char* add_tmp = new char[sizeof(DEVICE)];
                        	DEVICE* add = (DEVICE*)add_tmp;

                      for(res = node->children;res;res = res->next){
                        printf("res name is  %s\n",res->name);
                        if(xmlStrcasecmp(res->name,BAD_CAST"id")==0){
                                id = xmlNodeGetContent(res);
                                memcpy(add->title,(char*)id,strlen((char*)id));
                                printf("id  is\n  %s\n",id);
                            }
                        else if(xmlStrcasecmp(res->name,BAD_CAST"passwd")==0){
                                passwd = xmlNodeGetContent(res);
                                printf("passwd is\n  %s\n",passwd);
                            }

                        else if(xmlStrcasecmp(res->name,BAD_CAST"type")==0){
                                type = xmlNodeGetContent(res);
                                printf("type is\n  %s\n",type);
                                add->Type = atoi((char*)type);
                            }
                        }
                        Login_device[fd] = add;

                        printf("Login_device.size is   %d\n",Login_device.size());
                        xmlFree(id);
                        xmlFree(passwd);
                        xmlFree(type);
                    /**********************************************/
							memcpy(write_buff,read_buff2,strlen(read_buff2));
							printf("write buff is \n%s\n ",write_buff);
							fd = Send(write_buff,strlen(write_buff));
							memset(write_buff,0,512);
							break;
                        }
                        else if(0==strcmp(p,"heartbeat")){
							Gettime();
							//printf("device heart beat\n");
							register_count++;
							printf("device heartbeat count is\n*******************\n*****     %d******\n*******************\\n",register_count/2);
							memcpy(write_buff,timebuff,512);
							printf("write buff is \n%s\n ",write_buff);
							fd = Send(write_buff,strlen(write_buff));
							memset(timebuff,0,512);
							memset(write_buff,0,512);
							break;
                        }
                        else if(0==strcmp(p,"alarm")){
							printf("device alarm\n");
							break;
                        }
                }
        }
    return fd;
}