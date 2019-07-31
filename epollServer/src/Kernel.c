#include"Kernel.h"

pool_t* m_pool;

MessageMap m_MessageMapArray[] = {

	{0,0}
};

int Kernel_Init()
{
	if((m_pool = CreateThreadPool(500,5,100)) == NULL)
	{
		perror("create thread poll call faild");
		return -1;
	}

	if(InitMySql() == -1)
		return -1;

	if(ConnectMySql("localhost","root","980701","zhihu") == -1)
	{
		perror("MySql connect call faild");
		return -1;
	}
	if(InitSocket() == -1)
		return -1;
}
int Kernel_Destory()
{
	if(DestroyThreadPool(m_pool) == 0 )
	{
		perror("destory threadpoll call faild");
		return -1;
	}

	DisConnect();

	if(Destory() ==-1)
		return -1;
}
int Text()
{
	char szsql[100] = {0};
	List* lststr;
	L_Init(&lststr);

	sprintf(szsql,"select r_id,login_name from login where password = '123456'");
	SelectMySql(szsql,2,lststr);
	if(lststr->nCount >0)
	{
		char strname[100] = {0};
		strcpy(strname,L_Front(lststr));
		L_Pop(lststr,strname);
		char strpwd[100] = {0};
		strcpy(strpwd,L_Front(lststr));
		L_Pop(lststr,strpwd);

		printf("r_id =%s\t login_name =%s",strname,strpwd);
	}
	return 0;
}
void MessageHandle(int clientfd,char* buf)
{
	char* pType = buf;
	int i = 0;
	while(1)
	{
		if(m_MessageMapArray[i].m_nType == *pType)
		{
			(*m_MessageMapArray[i].m_pFun)(clientfd,buf);
			break;
		}
		else if((m_MessageMapArray[i].m_nType == 0) && (m_MessageMapArray[i].m_pFun == 0))
			break;
		i++;
	}
}


