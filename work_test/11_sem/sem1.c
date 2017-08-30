#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
#include <pthread.h>  
#include <semaphore.h>
  
int myglobal;  
sem_t sem;  
  
void * thread_function(void *arg)  
{  
	int i,j;  
	for (i = 0; i < 10; i += 1)  
	{  
		sem_wait(&sem);  
		j = myglobal;  
		j = j+1;  
		printf(".");  
		fflush(stdout);  
		sleep(1);  
		myglobal = j;  
		sem_post(&sem);  
	}  
	return NULL;  
}  
  
  
int main(void)  
{  
	pthread_t mythread;  
	int i;  
  
	sem_init(&sem, 0, 1);//信号量初始化   
	if(pthread_create(&mythread, NULL, thread_function, NULL))  
	{  
		printf("create thread error!\n");  
		abort();  
	}  
  
/*  sleep(1);*/  
  
	for(i = 0; i < 10; i++)  
	{  
		sem_wait(&sem);//=0   
		myglobal = myglobal + 1;  
		printf("o");  
		fflush(stdout);  
		sleep(1);  
		sem_post(&sem);//=1   
	}  
  
	if(pthread_join(mythread, NULL))  
	{  
		printf("waiting thread failed!\n");  
		abort();  
	}  
  
	printf("myglobal equals %d\n",myglobal);  
	
	sem_destroy(&sem);
	exit(0);  
}  
