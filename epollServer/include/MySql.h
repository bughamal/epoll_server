#ifndef _MYSQL_H
#define _MYSQL_H

//#include <//use//include//mysql//mysql.h>
#include <mysql.h>
#include"List.h"

int InitMySql();
int  ConnectMySql(char *host,char *user,char *pass,char *db);
void  DisConnect();
int  SelectMySql(char* szSql,int nColumn,List *lstStr); 

int UpdateMySql(char* szSql);
 

extern MYSQL sock;   
extern MYSQL_RES *results;   
extern MYSQL_ROW record; 




#endif
