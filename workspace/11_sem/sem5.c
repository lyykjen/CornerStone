/*
*这个程序实现同时运行两个线程，一个控制输入，另一个控制处理统计和输出(小写转大写)。
*输入end则退出
*Taken from http://blog.csdn.net/ljianhui/article/details/10813469/
*/
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//线程函数
void *thread_func(void *msg);
sem_t sem;//信号量
sem_t sem_add;//增加的信号量
#define MSG_SIZE 512

int main(int argc, char *argv[])
{
	pthread_t thread;
	void *thread_result = NULL;
	char msg[MSG_SIZE];
	//初始化信号量,初始值为0
	if(sem_init(&sem, 0, 0) == -1)
	{
		perror("semaphore intitialization failed\n");
		exit(EXIT_FAILURE);
	}
	//初始化信号量,初始值为1
	if(sem_init(&sem_add, 0, 1) == -1)
	{
		perror("semaphore intitialization failed\n");
		exit(EXIT_FAILURE);
	}
	//创建线程，并把msg作为线程函数的参数
	if(pthread_create(&thread, NULL, thread_func, msg))
	{
		perror("pthread_create failed\n");
		exit(EXIT_FAILURE);
	}
	//输入信息，以输入end结束，由于fgets会把回车（\n）也读入，所以判断时就变成了“end\n”
	printf("Input some text. Enter 'end'to finish...\n");

	sem_wait(&sem_add);
	while(strcmp("end\n", msg) != 0)
	{
		if(!fgets(msg, MSG_SIZE, stdin))
		{
			printf("input error\n");
		}

		if(strncmp("test", msg, 4) == 0)
		{
			sem_post(&sem);//把信号量加1
			sem_wait(&sem_add);//把sem_add的值减1，即等待子线程处理完成
			strcpy(msg, "copy_data\n");
		}

		sem_post(&sem);//把信号量加1
		sem_wait(&sem_add);//把sem_add的值减1，即等待子线程处理完成
	}


	printf("Waiting for thread to finish...\n");
	//等待子线程结束
	if(pthread_join(thread, &thread_result))
	{
		perror("pthread_join failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	//清理信号量
	sem_destroy(&sem);
	sem_destroy(&sem_add);
	exit(EXIT_SUCCESS);
}


void* thread_func(void *msg)
{
	char *ptr = msg;

	while(msg)
	{
		sem_wait(&sem);//等待信号量，把信号量减
		if(!strcmp("end\n", msg))
		{
			break;
		}

		int i = 0;
		//把小写字母变成大写
		for(; ptr[i] != '\0'; ++i)
		{
			if(ptr[i] >= 'a' && ptr[i] <= 'z')
			{
				ptr[i] -= 'a' - 'A';
			}
		}
		printf("You input %d characters\n", i-1);
		printf("To Uppercase: %s\n", ptr);

		sem_post(&sem_add);//把信号量加1,表明子线程处理完成
	}
	sem_post(&sem_add);
	//退出线程
	pthread_exit(NULL);
}
