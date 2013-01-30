#include "../include/Xepoull.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

//extern char write_buff[512];

epoll_event Xepoll::ev;
epoll_event Xepoll::events[20];


int Xepoll::epfd;
Xepoll::Xepoll()
{
	RunFlag = true;
}

Xepoll::~Xepoll()
{
	//dtor
}

int Xepoll::Init()
{
	epfd=epoll_create(256);
	struct sockaddr_in serveraddr;

	int ret = listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(ret<0){
        printf("build socket error\n");
    }
	ev.data.fd=listenfd;
	ev.events=EPOLLIN;
	epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port=htons(3100);

	ret = bind(listenfd,(sockaddr*)&serveraddr,16);
	if(ret<0){
        printf("bind error\n");
	}

	ret = listen(listenfd,20);
    if(ret<0){
        printf("listen error\n");
    }
	return 0;
}

int Xepoll::Uninit()
{
	RunFlag = false;
	return 0;
}

void* Xepoll::Task(void* arg)
{
    OBJ_DEIVCE* New_Device = (OBJ_DEIVCE*)arg;

    int fd = New_Device->New_Obj->Xml_Ans(((OBJ_DEIVCE*)arg)->buff,((OBJ_DEIVCE*)arg)->New_Obj->m_Sockfd);
    //New_Device->New_Obj->Send(write_buff,strlen(write_buff));

   // memset(write_buff,0,512);
    if(fd!=0){
//        ev.data.fd=fd;
//        ev.events=EPOLLIN;
//        epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev);
        delete [] New_Device->buff;
        delete New_Device;
    }


}


int Xepoll::Listen()
{
	while(RunFlag)
	{

		int nfds=epoll_wait(epfd,events,20,500);
        int sockfd;
		for(int i=0;i<nfds;++i)
		{
			if(events[i].data.fd == listenfd)
			{
			    sockaddr_in clientaddr;
			    socklen_t clint_len;
				int connfd = accept(listenfd,(sockaddr*)&clientaddr,&clint_len);
				char *str = inet_ntoa(clientaddr.sin_addr);
                printf("new login is   %s\n",str);

				Sockfd_Map[connfd] = new Xepoll_Client(connfd);
                printf("new sock connect is builed\n");
				ev.data.fd=connfd;
				ev.events=EPOLLIN;
				epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
			}
			else if(events[i].events & EPOLLIN)
			{
				if ( (sockfd = events[i].data.fd) < 0)
				{
					continue;
				}
				char *Read_buff = new char[512];
                memset(Read_buff,0,512);
				int read_len = read(sockfd,Read_buff,512);
				if(0== read_len){
                    close(sockfd);
                    iter = Sockfd_Map.find(sockfd);
                    Xepoll_Client* del_client = Sockfd_Map[sockfd];
                    delete [] (char*)del_client;
                    Sockfd_Map.erase(iter);


//                    iter_login = Xepoll_Client::Login_device.find(sockfd);
//                    DEVICE* del_device_node = Xepoll_Client::Login_device[sockfd];
//                    delete del_device_node;
//                    Xepoll_Client::Login_device.erase(iter_login);

                    Xepoll_Client::Login_device.size();



                    printf("read len is zero\n");
                    continue;
				}
								//Read_buff[read_len+1] = '\0';
				//printf("Xepoll_Client::Login_device.size is   %d\n",Xepoll_Client::Login_device.size());

				ev.data.fd=sockfd;
				ev.events=EPOLLOUT;
				epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
                printf("recv buff is\n%s\n",Read_buff);

                OBJ_DEIVCE* tmp = new OBJ_DEIVCE;
				tmp->buff = Read_buff;
				tmp->New_Obj = Sockfd_Map[sockfd];
				pthread_t new_obj;
                pthread_create(&new_obj,NULL,Xepoll::Task,(void*)tmp);
                ev.data.fd=sockfd;
                ev.events=EPOLLIN;
                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
			}

          }
	}
	return 0;
}
