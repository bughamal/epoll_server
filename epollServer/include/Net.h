#ifndef _NTE_H
#define _NTE_H




#include "thread_pool.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <sys/epoll.h>
#include "Kernel.h"

#define SERVERIP "192.168.73.130"
#define SERVERPORT 8000
#define IPSIZE 16
#define BUFSIZE 1500
#define EPOLLSIZE 500

extern int m_blag;
extern int m_epfd;
extern int m_serverfd;

int InitSocket();
int ConnectClient(pool_t* m_pool);
int Destory();
int SendData(int clientfd,char* buf,int bufsize);
void* Jobs(void* arg);

#endif
