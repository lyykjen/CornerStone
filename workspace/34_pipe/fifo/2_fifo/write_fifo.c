#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 655360

int main(int argc,char *argv[])
{
	int n,fd;
	char buf[MAX];

	if(argc < 2)
	{
		fprintf(stderr,"usage : %s argv[1].\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if(mkfifo(argv[1],0666) < 0 && errno != EEXIST)
	{
		fprintf(stderr,"Fail to mkfifo %s : %s.\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}

	if((fd = open(argv[1],O_WRONLY )) < 0)
	{
		fprintf(stderr,"Fail to open %s : %s.\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("open for write success.\n");

	while(1)
	{
		printf(">");
		scanf("%d",&n);

		n = write(fd,buf,n);
		printf("write %d bytes.\n",n);
	}
	
	exit(EXIT_SUCCESS);
}