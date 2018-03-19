/*
*两个线程同时向屏幕输出字符，竞争信号量资源(也就是输出到屏幕)
*/
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
	for (int i = 0; i < 10; i += 1)  
	{  
		sem_wait(&sem);  
		myglobal++;  
		printf("￥");//向屏幕中输出数据 
		fflush(stdout);  
		sleep(rand() % 3);
		printf("￥");//再一次向屏幕中输出数据 
		fflush(stdout); 
		sem_post(&sem);
		sleep(rand() % 2);		
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
  
	for(i = 0; i < 10; i++)  
	{  
		sem_wait(&sem);//=0   
		myglobal++;  
		printf("#");//向屏幕中输出数据
		fflush(stdout); 
		sleep(rand() % 3);//休眠随机时间	
		printf("#");//再一次向屏幕中输出数据
		fflush(stdout); 
		sem_post(&sem);//=1
		sleep(rand() % 2);//休眠随机时间
	}  
  
	if(pthread_join(mythread, NULL))  
	{  
		printf("waiting thread failed!\n");  
		abort();  
	}  
  
	printf("\nmyglobal equals %d\n",myglobal);  
	
	sem_destroy(&sem);
	exit(0);  
}  
