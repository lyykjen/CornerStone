#include<stdio.h>

unsigned int TestAsOne0(char log) 
{ 
	int i; 
	unsigned int num=0, val; 
	for(i=0; i<8; i++) 
	{ 
		val = log >> i;  // 移位		
		if(val&0x01) 
		num++; 
	} 
	return num; 
} 
void main()
{
	int var;
	scanf("%d",&var);
	printf("count one:%d\n",TestAsOne0(var));
}