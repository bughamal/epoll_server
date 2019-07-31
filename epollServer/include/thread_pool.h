#ifndef _THREAD_POLL_H
#define _THREAD_POLL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0
#define _DEF_LIMIT 10
#define TIME_OUT   3

typedef struct 
{
	void* (*task)(void*);
	void* arg;
}task_t;

typedef struct 
{
	int shutdown;

	int thread_max;
	int thread_min;
	int thread_alive;
	int thread_busy;
	int thread_kill;

	int queue_max;
	int queue_head;
	int queue_tail;
	int queue_cur;
	task_t* task;

	pthread_cond_t not_empty;
	pthread_cond_t not_full;
	pthread_mutex_t lock_task;

	pthread_t* arr_pthread_tid;
	pthread_t manage_tid;
}pool_t;
pool_t* CreateThreadPool(int max,int min,int queue_max);
int DestroyThreadPool(pool_t*);
void* ManagerThreadPool(void*);
int Addtask(pool_t*,void* (*task)(void*),void* arg);
void* ConsumeTask(void*);
int if_thread_alive(pthread_t tid);

#endif
