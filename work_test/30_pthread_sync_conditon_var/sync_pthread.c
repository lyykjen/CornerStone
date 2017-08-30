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