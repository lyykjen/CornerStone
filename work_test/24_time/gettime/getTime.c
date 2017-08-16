#include <stdio.h>
#include <time.h>
 
int main(void)
{
#if 0	
    time_t now;
    struct tm *tm_now;
 
    time(&now);
    tm_now = gmtime(&now);
 
    printf("now datetime: %d-%d-%d %d:%d:%d\n",\
	tm_now->tm_year, tm_now->tm_mon, tm_now->tm_mday,\
	tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
#endif

#if 0
    time_t timep;  
     
    time(&timep); /*获取time_t类型的当前时间*/  
    /*用gmtime将time_t类型的时间转换为struct tm类型的时间，按没有经过时区转换的UTC时间 
      然后再用asctime转换为我们常见的格式 Fri Jan 11 17:25:24 2008 
    */  
    printf("%s", asctime(gmtime(&timep)));  //打印UTC时间
#endif


    time_t timep;  
	time(&timep); /*获取time_t类型当前时间*/     
    /*转换为常见的字符串：Fri Jan 11 17:04:08 2008*/  
    printf("%s", ctime(&timep));  转换UTC时间为本地区时时间
    return(0);
}
