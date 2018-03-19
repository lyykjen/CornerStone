#include<stdio.h>

//printf("%s %s [%d]: ", __FILE__, __FUNCTION__, __LINE__);

#define PRINT_DBG(debug, ...)\
{\
    if(debug) {\
    printf(__VA_ARGS__);\
    }\
	else{\
		printf(__VA_ARGS__,);\
	}\
}
#define MACRO(s, ...) printf(s, ##__VA_ARGS__)


int main()
{
	int i =100;
	PRINT_DBG(1,"hello\n");
	PRINT_DBG(0,"world, %d\n",i);
	MACRO("hello, world\n"); //这里没有可变参数， 所以要用##__VA_ARGS__
	MACRO("hello, %s\n", "fanrey");
	return 0;
}
