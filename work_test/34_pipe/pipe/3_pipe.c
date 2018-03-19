/*
父进程读取文件的内容，写到无名管道，子进程从管道中读取内容写到另一个文件。
运行结果：父进程先退出，子进程后退出；
原因：父进程读完文件后read返回0，关闭写管道，子进程读不到数据而且写已经关闭，从而也返回0.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX 100

int child_work(int pfd,char *fname)
{
	int n,fd;
	char buf[MAX];

	if((fd = open(fname,O_WRONLY | O_CREAT | O_TRUNC,0666)) < 0)
	{
		fprintf(stderr,"Fail to open %s : %s.\n",fname,strerror(errno));
		return -1;
	}

	while( n = read(pfd,buf,sizeof(buf)) )
	{
		write(fd,buf,n);
	}
	
	if(n==0)
	{
		printf("read is over\n");
	}
	
	close(pfd);

	return 0;
}

int father_work(int pfd,char *fname)
{
	int fd,n;
	char buf[MAX];

	if((fd = open(fname,O_RDONLY)) < 0)
	{
		fprintf(stderr,"Fail to open %s : %s.\n",fname,strerror(errno));
		return -1;
	}

	while(n = read(fd,buf,sizeof(buf)))
	{
		write(pfd,buf,n);
	}
	
	if(n==0)
	{
		printf("write is over\n");
	}
	close(pfd);

	return 0;
}

int main(int argc,char *argv[])
{
	int pid;
	int fd[2];

	if(argc < 3)
	{
		fprintf(stderr,"usage %s argv[1] argv[2].\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if(pipe(fd) < 0)
	{
		perror("Fail to pipe");
		exit(EXIT_FAILURE);
	}

	if((pid = fork()) < 0)
	{
		perror("Fail to fork");
		exit(EXIT_FAILURE);
	
	}else if(pid == 0){
		
		close(fd[1]);
		child_work(fd[0],argv[2]);
	
	}else{
	
		close(fd[0]);
		father_work(fd[1],argv[1]);
		wait(NULL);
	}

	exit(EXIT_SUCCESS);
}