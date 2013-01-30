#ifndef XEPOLL_CLIENT_H
#define XEPOLL_CLIENT_H
#include <map>

using namespace std;

void ReadXml();
 typedef struct _DEVICE{
        char name[60];
        char title[16];
        int Type;
        int ID;
        int PID;
        int Obj_Type;
        int Media_Type;
        char stream[60];
 }DEVICE,*LPDEVICE;

class Xepoll_Client
{
	public:
		Xepoll_Client(int sockfd);
		virtual ~Xepoll_Client();
		int Xml_Ans(char* buff,int fd);
		int Send(char *Buffer,int Len);
		int Recv(char *Buffer,int Size);
		void Gettime(void);
        static map<int,DEVICE*> Login_device;
        map<int,DEVICE*>::iterator iter_login;
		int m_Sockfd;
	protected:
	private:
		char timebuff[512];
};

#endif // XEPOLL_CLIENT_H
