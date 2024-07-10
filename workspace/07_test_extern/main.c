#include<stdio.h>
#include"main.h"
#include <pthread.h>
#include <unistd.h>

int cnt = 0;
handle_data_t msg;

pthread_cond_t cond;
pthread_mutex_t mutex;
int flag = 1;

int main(int argc ,char ** argv)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	
	
	
	cnt = 1;
	printf("This is main function!\n");
	msg.b = 1;
	fun();
	printf("cnt = %d\n",cnt);
	
	msg.a = 1;
	
	printf("msg.a = %d\n",msg.a);
	printf("msg.b = %d\n",msg.b);
	
	char c ;
	while ((c = getchar()) != 'q');
	printf("Now terminate the thread!\n");

	pthread_mutex_lock(&mutex);
	flag = 0;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	printf("Wait for thread to exit\n");
	pthread_join(thread, NULL);
	printf("Bye\n");
	return 0;
}