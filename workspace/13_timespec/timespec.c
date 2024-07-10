#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>
#include <time.h>

/*
struct timespec
{
    time_t tv_sec;       
    long int tv_nsec;      
};
*/


int main()
{
	struct timespec timeout;
	timeout.tv_sec= time(0) + 1; //time(0) 代表的是当前时间 而tv_sec 是指的是秒
	timeout.tv_nsec=0;  
	//printf("time(0) =  %ld\n",time(0));	
	//sleep(1);
	//gettimeofday(&tv,NULL);
	printf("time(0) =  %ld\n",time(0));
	printf("time %ld:%ld\n",timeout.tv_sec - time(0) ,timeout.tv_nsec);
	
	
	return 0;
}