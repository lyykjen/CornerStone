/*
父进程向管道中写数据，子进程从管道中读取数据
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define N 10
#define MAX 100

int child_read_pipe(int fd)
{
	char buf[N];
	int n = 0;

	while(1)
	{
		n = read(fd,buf,sizeof(buf));
		buf[n] = '\0';

		printf("Read %d bytes : %s.\n",n,buf);

		if(strncmp(buf,"quit",4) == 0)
			break;
	}

	return 0;
}

int father_write_pipe(int fd)
{
	char buf[MAX] = {0};
	
	while(1)
	{
		printf(">");
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';
		write(fd,buf,strlen(buf));
		usleep(500);
		if(strncmp(buf,"quit",4) == 0)
			break;
	}

	return 0;
}

int main()
{
	int pid;
	int fd[2];

	if(pipe(fd) < 0)
	{
		perror("Fail to pipe");
		exit(EXIT_FAILURE);
	}

	if((pid = fork()) < 0)
	{
		perror("Fail to fork");
		exit(EXIT_FAILURE);

	}else if(pid == 0){//child

		close(fd[1]);//关闭写
		child_read_pipe(fd[0]);

	}else{//father		
		close(fd[0]);//关闭读
		father_write_pipe(fd[1]);
	}
	
	exit(EXIT_SUCCESS);
}

/*
从以上验证我们可以看到：
<1>当写端存在时，管道中没有数据时，读取管道时将阻塞
<2>当读端请求读取的数据大于管道中的数据时，此时读取管道中实际大小的数据
<3>当读端请求读取的数据小于管道中的数据时，此时放回请求读取的大小数据
*/