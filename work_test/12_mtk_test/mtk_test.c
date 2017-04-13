#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADD(x,y) x+y

int main()
{
	int m = 3;
	char c;
	m+=m*ADD(m,m);
	printf("m = %d\n",m);
	while((c=getchar())!='a')
		putchar(c);
	return 0;
}