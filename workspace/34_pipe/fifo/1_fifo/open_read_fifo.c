#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int fd;

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

	if((fd = open(argv[1],O_RDONLY)) < 0)
	{
		fprintf(stderr,"Fail to open %s : %s.\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("open for read success.\n");
	
	return 0;
}