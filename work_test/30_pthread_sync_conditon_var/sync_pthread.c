#include <unistd.h>  
#include <stdio.h> 
#include <pthread.h>  
#include <stdbool.h>  
  
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;  
bool awake_ok_flag = false;

static void *proc_handle_thread(void *arg)  
{
	while(true)
	{
		pthread_mutex_lock(&mutex);//这个mutex主要是用来保证pthread_cond_wait的并发性  
		/*
		 *下面这个while要特别说明一下，单个pthread_cond_wait功能很完善，
		 *为何这里要有一个while(!awake_ok_flag)呢？因为pthread_cond_wait里的线程可能会被意外唤醒，
		 *如果这个时候awake_ok_flag = false，则不是我们想要的情况。这个时候，应该让线程继续进入pthread_cond_wait 
		*/
		while(!awake_ok_flag)
		{
			 pthread_cond_wait(&cond, &mutex);
		}
		awake_ok_flag = false;
		pthread_mutex_unlock(&mutex); //pthread_cond_wait会先解除之前的pthread_mutex_lock锁定的mutex，
									  //然后阻塞在等待对列里休眠，直到再次被唤醒（大多数情况下是等待的条件成立而被唤醒），
									  //唤醒后,该进程会先锁定先pthread_mutex_lock(&mutex)，再读取资源  
		printf("hello sync pthread\n");
	}
	
	return 0;
}

int main(void)  
{
	printf("main thread start\n");	
	pthread_t pid;
	pthread_create(&pid, NULL, proc_handle_thread, NULL); 
	printf("proc_handle_thread start\n");
	
	for (int i = 0; i < 10; i++) 
	{  	
		pthread_mutex_lock(&mutex); 			
		awake_ok_flag = true;
		pthread_cond_signal(&cond);  	
		pthread_mutex_unlock(&mutex);  
		
		usleep(500000); //500ms
	}
	 pthread_cancel(pid);  
	 printf("child thread exit\n");	
	 pthread_join(pid, NULL);  
	 printf("main thread exit\n");
	return 0;
}