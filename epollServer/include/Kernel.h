#ifndef _KERNEL_H
#define _KERNEL_H

#include<stdio.h>
#include"Net.h"
#include"MySql.h"
#include"thread_pool.h"
#include"Packdef.h"
#include<sys/stat.h>
#include<fcntl.h>

extern pool_t* m_pool;


typedef void(*PFUN)(int clientfd,char* buf);

typedef struct
{
	char m_nType;
	PFUN m_pFun;
}MessageMap;

void VedioRecv(int clientfd,char* arg);
void RegisterRQ(int clientfd,char* arg);
void LoginRQ(int clientfd,char* arg);
int Kernel_Init();
int Kernel_Destory();
int Text();
void MessageHandle(int clientfd,char* buf);




#endif
