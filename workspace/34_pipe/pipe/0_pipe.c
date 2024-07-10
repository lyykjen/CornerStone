/*测试一下管道的大小:65536*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	int count = 0;
	
	if(pipe(fd)<0)
	{
		perror("Fail to create pipe");
		exit(EXIT_FAILURE);
	}
	
	while(1)
	{
		write(fd[1],"a",sizeof(char));//一旦管道"满"了，写操作会一直阻塞在这里
		printf("count = %d.\n",++count);
	}
	return 0;
}