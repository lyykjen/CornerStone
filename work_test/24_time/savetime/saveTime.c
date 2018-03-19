#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

int main()
{
	FILE *fp = NULL;
	time_t now;
	struct tm *curTime;
	 
	char filename[256];
	while(1)
	{
	   now = time(NULL);
	   curTime = localtime(&now);
/*	   
	   sprintf(filename,"%04d-%02d-%02d %02d-%02d-%02d",curTime->tm_year+1900,
			curTime->tm_mon+1,curTime->tm_mday,curTime->tm_hour,curTime->tm_min,
			curTime->tm_sec);
	   fp = fopen(filename,"w");
	   fclose(fp);
*/	printf("%04d%02d%02d%02d%02d%02d\n",curTime->tm_year+1900,
			curTime->tm_mon+1,curTime->tm_mday,curTime->tm_hour,curTime->tm_min,
			curTime->tm_sec);
	   sleep(3);
	}
}