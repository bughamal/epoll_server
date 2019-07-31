#include "MySql.h"

MYSQL sock;
MYSQL_RES * results;
MYSQL_ROW record;

int InitMySql()
{
	if(NULL == mysql_init(&sock))
	{
		perror("mysql init  call faild");
		return -1;
	}
	mysql_set_character_set(&sock,"gb2312"); 
}



void DisConnect()
{
	mysql_close(&sock);

}

int ConnectMySql(char *host,char *user,char *pass,char *db)
{

	if (!mysql_real_connect(&sock, host, user, pass, db, 0, NULL, CLIENT_MULTI_STATEMENTS))
	{
		return -1;
	}
	mysql_query(&sock,"SET NAMES UTF8");
	return 0;
}

int SelectMySql(char* szSql,int nColumn,List* lstStr)
{
	if(mysql_query(&sock,szSql))return -1;

	results=mysql_store_result(&sock);
	if(NULL == results)return -1;
	while (record = mysql_fetch_row(results))
	{

		for(int i = 0;i < nColumn;i++)
		{
			// lstStr.push_back(record[i]);
			L_Push(lstStr,record[i]);

		}

	}

	return 0;
}

int UpdateMySql(char* szSql)
{
	if(!szSql)return -1;
	if(mysql_query(&sock,szSql))return -1;
	
	return 0;
}


