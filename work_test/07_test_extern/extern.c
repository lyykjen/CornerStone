#include <stdio.h>
#include "main.h"

pthread_t thread;

void * thread_extern_func(void *arg)
{
	pthread_mutex_lock(&mutex);
	while (flag) {
	printf("*****flag = %d\n",flag);
	pthread_cond_wait(&cond,&mutex);	
	}
	
	
	pthread_mutex_unlock(&mutex);
	printf("cond thread exit\n");
	return 0;
}

void fun()
{
	cnt = 2;
	msg.b = 2;
	
	if (0 != pthread_create(&thread, NULL, thread_extern_func, NULL)) {
	printf("error when create pthread\n");
	}	
}
