#include"List.h"

void L_Init(List **plist)
{
	*plist = (List*)malloc(sizeof(List));
	(*plist)->nCount = 0;
	(*plist)->pHead = NULL;
	(*plist)->pTail = NULL;
}

void L_Push(List *pList,char* str_str)
{
	if(pList == NULL)return;

	MyList *pTemp = NULL;
	pTemp = (MyList*)malloc(sizeof(MyList));
	strcpy(pTemp->str,str_str);
	pTemp->pNext = NULL;


	//尾添加
	if(pList->pHead == NULL)
	{
		pList->pHead = pTemp;
	}
	else
	{
		pList->pTail->pNext = pTemp;
	}
	pList->pTail = pTemp;

	pList->nCount++;
}
char* L_Front(List *pList)
{
	if(pList == NULL) return NULL;
	return pList->pHead->str;
}
int L_Pop(List *pList,char* tempstr)
{
	if(pList == NULL || pList->nCount == 0)return -1;

	MyList *pDel = NULL;
	MyList* temp = NULL;
	pDel = pList->pHead;
	if(strcmp(pList->pHead->str,tempstr) == 0)
	{
		temp = pDel;
		pList->pHead = pList->pHead->pNext;
	}
	else
	{
		while(pDel->pNext != NULL)
		{
		if(strcmp(pDel->pNext->str,tempstr) == 0)
			{
				temp = pDel->pNext;
				pDel = temp->pNext;
				break;
			}
			pDel = pDel->pNext;
		}
	}



	free(temp);
	temp = NULL;
	pList->nCount--;
	if(pList->nCount == 0)
	{
		pList->pTail = NULL;
	}

	
	return 0;
}
int L_Traverse(List *pList,char* str[])
{
	if(pList == NULL || pList->nCount == 0)return -1;
	MyList *pFid = NULL;
	pFid = pList->pHead;
	int i=0;
	while(pFid != NULL)
	{
		strcpy(str[i], pFid->str);
		i++;
		pFid = pFid->pNext;
	}
	return 1;
}

int L_IsEmpty(List *pList)
{
	if(pList == NULL)exit(1);

	return pList->nCount == 0?1:0;
}


