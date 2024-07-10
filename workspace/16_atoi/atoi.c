#include <stdlib.h>
#include <stdio.h>
#include <math.h>
 
int main(void)
{
    int n;
    char *str = "12345.67";
    n = atoi(str);
    printf("n=%d\n",n);
	printf("n=%.1f\n",12345.67);
	printf("roundf(12345.67)=%.1f\n",roundf(12345.67));
	printf("str2 = %d\n",atoi("123"));
	printf("str2 = %d\n",'A');
	printf("str2 = %c\n",65);
	printf("sizeof(unsigned long int) = %ld\n",sizeof(unsigned long int));
	//printf("atoi('A') = %d\n",atoi('A'));//error ,Segmentation fault (core dumped)
	printf("toascii('A') = %d\n",toascii('A'));	
    return 0;
}