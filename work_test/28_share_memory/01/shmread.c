#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include <sys/shm.h>  
#include "shmdata.h"  
  
int main()
{  
	//创建共享内存,获取共享内存标识符 
	int shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);  
	if(shmid == -1)  
	{  
		fprintf(stderr, "shmget failed\n");  
		exit(EXIT_FAILURE);  
	}  
	//将共享内存连接到当前进程的地址空间  
	void *shm = shmat(shmid, 0, 0);  
	if(shm == (void*)-1)  
	{  
		fprintf(stderr, "shmat failed\n");  
		exit(EXIT_FAILURE);  
	}  
	printf("\nMemory attached at %p\n", shm);  
	//设置共享内存  
	struct shared_use_st *shared = (struct shared_use_st*)shm;  
	shared->written = true;  
	while(1)//读取共享内存中的数据  
	{  
		//没有进程向共享内存写数据,数据可读取  
		if(shared->written != true)  
		{  
			printf("You wrote: %s", shared->text);  
			sleep(rand() % 3);  
			//读取完数据，设置written使共享内存段可写  
			shared->written = true;  
			//输入了end，退出循环（程序）  
			if(!strncmp(shared->text, "end", 3))  
				break;  
		}  
		else//有其他进程在写数据，不能读取数据  
			sleep(1);  
	}  
	//把共享内存从当前进程中分离  
	if(shmdt(shm) == -1)  
	{  
		fprintf(stderr, "shmdt failed\n");  
		exit(EXIT_FAILURE);  
	}  
	//删除共享内存  
	if(shmctl(shmid, IPC_RMID, 0) == -1)  
	{  
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");  
		exit(EXIT_FAILURE);  
	}  
	exit(EXIT_SUCCESS);  
}  