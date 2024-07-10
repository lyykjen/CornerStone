#include <stdio.h>
#include <unistd.h>
#include "main.h"

#define SDCARD_PATH       "./"
static const char *F_PATH = SDCARD_PATH "/test.log";
static const char *F_TRIG = SDCARD_PATH "/trigger";
FILE *stream = NULL;
int total_num;

void ync_camera_log_init()
{
	//We will add better method to trigger log print.
	//For the time being, we just check if the trigger file exists.
	if (access(F_TRIG, F_OK) == 0)
	{
		stream = fopen(F_PATH, "a");
		if (stream == NULL)
		{
			total_num = 0;
			printf("open logfile fail\n");
		}
		else
		{
			fprintf(stream, "\n=========================\n");
		}
	}
}

void ync_camera_log_remove()
{
	if (stream != NULL)
	{
		fclose(stream);
		stream = NULL;
	}
}

int main()
{	
	ync_camera_log_init();
	YNC_LOGPRINT(1,"test1");
	YNC_LOGPRINT(0,"test2");
	return 0;
}