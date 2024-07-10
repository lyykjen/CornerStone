#include<stdio.h>
void main()                                                
{                                          
	int a;                                                         
	scanf("%d",&a);                                    
	printf("%c \n",(a)&(a-1)?'n':'y'); //   若是打印y，否则n          
}
