#ifndef XEPOULL_H
#define XEPOULL_H


#include <sys/epoll.h>
#include "Xepoll_Client.h"
#include <unistd.h>


typedef struct _OBJ_DEIVCE{

    Xepoll_Client *New_Obj;
    char* buff;

}OBJ_DEIVCE;



class Xepoll
{
	public:
		Xepoll();
		virtual ~Xepoll();

		int Init();
		int Uninit();
		int Listen();
		static void* Task(void* arg);
        static int epfd;
        static struct epoll_event ev,events[20];

	protected:

	private:

	map<int,Xepoll_Client*>Sockfd_Map;
	map<int,Xepoll_Client*>::iterator iter;
    map<int,DEVICE*>::iterator iter_login;




	bool RunFlag;
	//char Read_buff[512];
    int listenfd;


	//int Listen_Sockfd;

};

#endif // XEPOULL_H
