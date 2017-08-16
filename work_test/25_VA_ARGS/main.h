#ifndef _MAIN_H_
#define _MAIN_H_
#include <time.h>

extern FILE *stream;
extern int total_num;

#ifdef __cplusplus
extern "C" {
#endif
void ync_camera_log_init();
void ync_camera_log_remove();

#ifdef __cplusplus
}
#endif
/*
//fprintf(stream,#X":",##__VA_ARGS__);\
		//fprintf(stream,"[Total:%03d]%s",++total_num,ctime(&timep));\
		//fflush(stream);
		YNC_LOGPRINT(1,"test"); 
*/

#define YNC_LOGPRINT(X,...) do{\
		if(X)\
		{\
			time_t timep;\
			time(&timep);\
			printf(__VA_ARGS__);\
			fprintf(stream,"[Total:%03d]%s",++total_num,ctime(&timep));\
			fflush(stream);\
		}\
		else\
		{\
			time_t timep;\
			time(&timep);\
			printf(__VA_ARGS__);\
			fprintf(stream,"[Total:%03d]%s",++total_num,ctime(&timep));\
			fflush(stream);\
		}\
}while(0)
#endif
