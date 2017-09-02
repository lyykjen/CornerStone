#include <unistd.h>  
#include <stdio.h> 
#include <pthread.h>  
#include <stdbool.h>  
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <math.h>
#include <inttypes.h>
 
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;  
bool awake_ok_flag = false;

uint64_t time_ms(void)
{
	long            ms; // Milliseconds
	time_t          s;  // Seconds
	struct timespec spec;

	clock_gettime(CLOCK_MONOTONIC, &spec);

	s  = spec.tv_sec;
	ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds

	return s * 1000 + ms;
}

void get_time_in(struct timespec *ts, float duration_s)
{
	// We would rather use CLOCK_MONOTONIC but it returns instantly,
	// so doesn't seem to work.
	clock_gettime(CLOCK_REALTIME, ts);

	const int secs = duration_s;
	const int64_t nsecs = (duration_s - (float)secs) * 1e9;

	ts->tv_sec += secs;
	ts->tv_nsec += nsecs;
}

static void *proc_handle_thread(void *arg)  
{
#if 0	
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
#else
	while(true)
	{		
		struct timespec ts;
		uint64_t waiting_started_ms = 0;
		pthread_mutex_lock(&mutex);
		
		//gettimeofday(&now, NULL);//gettimeofday()时间有时候并不精确，有时候甚至会出现“时光倒流”的情况
		get_time_in(&ts,3.0f);
		waiting_started_ms = time_ms();
		
		printf("wait start\n");
		if( 0 != pthread_cond_timedwait(&cond,&mutex,&ts))
		{				
			pthread_mutex_unlock(&mutex);
			printf("wait exit TIMEOUT took: %" PRIu64 " ms\n", time_ms() - waiting_started_ms);	
		}			
		else
		{
			pthread_mutex_unlock(&mutex);
			printf("wait exit OK took: %" PRIu64 " ms\n", time_ms() - waiting_started_ms);
			printf("hello sync pthread\n");
		}
	}
#endif	

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
		sleep(2);
		pthread_mutex_lock(&mutex); 			
		awake_ok_flag = true;
		pthread_cond_signal(&cond);  	
		pthread_mutex_unlock(&mutex);  
		
		//usleep(500000); //500ms
	}
	 pthread_cancel(pid);  
	 printf("child thread exit\n");	
	 pthread_join(pid, NULL);  
	 printf("main thread exit\n");
	return 0;
}