#ifndef _LIST_H
#define _LIST_H


#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct node
{
	char str[1024];
	struct node *pNext;
}MyList;

typedef struct node1
{
	int nCount;
	MyList *pHead;
	MyList *pTail;
}List;

void L_Init(List **plist);

void L_Push(List *pList,char* str_str);
char* L_Front(List *pList);
int L_Pop(List *pList,char* tempstr);
int L_Traverse(List *pList,char* str[]);

int L_IsEmpty(List *pList);



#endif
