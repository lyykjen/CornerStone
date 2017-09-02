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
		pthread_mutex_lock(&mutex);//���mutex��Ҫ��������֤pthread_cond_wait�Ĳ�����  
		/*
		 *�������whileҪ�ر�˵��һ�£�����pthread_cond_wait���ܺ����ƣ�
		 *Ϊ������Ҫ��һ��while(!awake_ok_flag)�أ���Ϊpthread_cond_wait����߳̿��ܻᱻ���⻽�ѣ�
		 *������ʱ��awake_ok_flag = false������������Ҫ����������ʱ��Ӧ�����̼߳�������pthread_cond_wait 
		*/
		while(!awake_ok_flag)
		{
			 pthread_cond_wait(&cond, &mutex);
		}
		awake_ok_flag = false;
		pthread_mutex_unlock(&mutex); //pthread_cond_wait���Ƚ��֮ǰ��pthread_mutex_lock������mutex��
									  //Ȼ�������ڵȴ����������ߣ�ֱ���ٴα����ѣ������������ǵȴ������������������ѣ���
									  //���Ѻ�,�ý��̻���������pthread_mutex_lock(&mutex)���ٶ�ȡ��Դ  
		printf("hello sync pthread\n");
	}
#else
	while(true)
	{		
		struct timespec ts;
		uint64_t waiting_started_ms = 0;
		pthread_mutex_lock(&mutex);
		
		//gettimeofday(&now, NULL);//gettimeofday()ʱ����ʱ�򲢲���ȷ����ʱ����������֡�ʱ�⵹���������
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