#include"Net.h"


int m_blag = 1;
int m_epfd;
int m_serverfd = 0;

int SendData(int clientfd,char* buf,int bufsize)
{
	if(clientfd <= 0 || buf == NULL || bufsize <=0)
	 return -1;

	 if(send(clientfd,(const char*)&bufsize,sizeof(int),0) <0)
    return -1;

	if(send(clientfd,buf,bufsize,0) < 0)
	 return -1;
			  
	 return 0;
}
void * Jobs(void * arg)
{
	struct sockaddr_in clientaddr;
	char ipstr[IPSIZE];
	char buf[BUFSIZE];
	int clientsize = sizeof(clientaddr);
	int  serverfd = (int)arg;
	int clientfd;
	/*建立链接*/
	if((clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,&clientsize))==-1)
	perror("Custom Thread Accept Error:");
	//输出客户端信息
	printf("Custom Thread Tid:0x%x\tClient ip:%s\tClient Port:%d\n",(unsigned int)pthread_self(),inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ipstr,sizeof(ipstr)),ntohs(clientaddr.sin_port));
	/*对客户端进行处理和响应*/
	int len;
	int nPackSize;
	char* pszbuf = NULL;
	int bufsize = 0;
	int offes = 0;
	//while(1)
//	{
		printf("aaa\n");
		len = recv(clientfd,(char*)&nPackSize,sizeof(int),0);
		printf("bbb\n");
		if(len <= 0)
		{
			close(clientfd);
		//	break;
		}
		pszbuf = (char*)malloc(nPackSize);
		bufsize = 0;
		printf("ccc\n");
		while(bufsize < nPackSize)
		{
			//offes = recv(clientfd,pszbuf+bufsize,nPackSize-bufsize,0);
			bufsize+=offes;
		}
		//处理函数
		printf("ddd\n");
		MessageHandle(clientfd,pszbuf);
		free(pszbuf);
		pszbuf = NULL;
	//}
}

int InitSocket()
{

 	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);

	if(inet_pton(AF_INET,SERVERIP,&serveraddr.sin_addr.s_addr) == -1)
	{
		perror("SERVERIP 转换失败");
		return -1;
	}
	//创建serversock
	if((m_serverfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("serverfd creat faild");
		return -1;
	}
	//bind
	if(bind(m_serverfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) == -1)
	{
		perror("bind faild");
	 	return -1;
	}
	//listen
	if(listen(m_serverfd,128) == -1)
	{
		perror("listen faild");
		return -1;
	}
	return 0;
}
int ConnectClient(pool_t* m_pool)
{
	if(!(m_serverfd >0))
	return -1;

	int ep_ready;
	//create epollfd;
	if((m_epfd = epoll_create(EPOLLSIZE)) == -1)
	{
		perror("epoll_create faild");
		return -1;
	}
	struct epoll_event e_eventarr[EPOLLSIZE];
	struct epoll_event e_event;
	//边缘触发
	e_event.events = EPOLLIN|EPOLLET;
	e_event.data.fd =m_serverfd;
	//添加监控事件
	if((epoll_ctl(m_epfd,EPOLL_CTL_ADD,m_serverfd,&e_event)) == -1)
	{
		perror("epoll ctl call faild");
		return -1;
	}
	// 监控sockfd
	while(m_blag)
	{
		ep_ready = epoll_wait(m_epfd,e_eventarr,EPOLLSIZE,-1);
		while(ep_ready--)
		{
		//	printf("%d\n",ep_ready);
		//	printf("fd = %d\n",e_eventarr[ep_ready].data.fd);
			 if(Addtask(m_pool,Jobs,(void*)e_eventarr[ep_ready].data.fd) == 0)
			 {
				perror("添加线程池任务失败");
				return -1;
			 }
		}
	}
	return 0;
}
int Destory()
{
	m_blag = 0;
	if(close(m_serverfd) == -1)
	{
		perror("close serverfd call faild");
		return -1;
	}
	if(close(m_epfd) == -1)
	{
		perror("close epfd call faild");
		return -1;
	}
	return 0;
}


