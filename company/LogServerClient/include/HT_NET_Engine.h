//HT_NET_Engine.h
#ifndef HT_NET_ENGINE_H
#define HT_NET_ENGINE_H

#ifdef __cplusplus
extern "C"
{
#endif

#define NET_CONNECT_EVENT 0X001
#define NET_CLOSED_EVENT 0x002
#define NET_RECV_ERROR_EVENT 0X003
#define NET_SEND_ERROR_EVENT 0X004
#define NET_WRITECOMPETE_EVENT 0x005

    typedef struct server_handler server_t;
    typedef struct connection_handler conn_t;

    typedef void (*RecvCallBack)(conn_t *conn, char *buf, int len, void *context);
    typedef void (*EventCallBack)(conn_t *conn, int eventtype, void *context, int error);

    int HT_NET_Engine_init(int threads, int maxConn);
    int HT_NET_Engine_init_nolog(int threads, int maxConn);

    int HT_NET_Engine_exit();

    server_t *Tcp_Server_Start(int listenPort,
            RecvCallBack recvcb, EventCallBack eventcb,
            void *context, int isPacket);
    int Tcp_Server_Closed(server_t *server);

    conn_t *Tcp_Connect(char *serverAddr, unsigned int port,
            RecvCallBack recvcb, EventCallBack eventcb,
            void *context, int isPacket, int timeout);

    void Tcp_SetContext(conn_t *conn, void *context);
    void *Tcp_GetContext(conn_t *conn);

    void Tcp_SetRecvCallBack(conn_t *conn, RecvCallBack recvcb);
    void Tcp_SetEventCallBack(conn_t *conn, EventCallBack eventcb);

    int Tcp_SendMsg(conn_t *conn, char *buf, int len);
    int Tcp_GetLocalAddr(conn_t *conn, char *buf, int len);
    int Tcp_GetRemoteAddr(conn_t *conn, char *buf, int len);

    int Tcp_Close(conn_t *conn);


    struct ht_iovec{
        void *iov_base; //data pointer
        unsigned int iov_len; //data len
    };
    
    int Tcp_SendMsgv(conn_t *conn, const struct ht_iovec *iov, int iovcnt);
    /*
     * struct ht_iovec buf[2];
     * buf[0].iov_len = 100;
     * buf[0].iov_base = malloc(100); //head
     * buf[1].iov_len = 200;
     * buf[2].iov_base = mallo(200); //data msg
     * Tcp_SendMsgv(conn, ht_iovec, 2);
    */
    
    

#ifdef __cplusplus
}
#endif

#endif
