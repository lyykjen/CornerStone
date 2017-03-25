/*
 Compile: gcc -o test test.c
 Execute: ./test /dev/ttyS1 /tmp/SD0 500000
			
*/
#include <stdio.h>  
#include <unistd.h>  

int main(int argc, char *argv[])  
{  
	int ch;  
	char *seg1,*seg2,*seg3;  
		
	getopt(argc,argv,"");

	seg1=argv[optind];  
	seg2=argv[optind+1];  
	seg3=argv[optind+2];  
	//printf("optopt %c\n",optopt);  
	printf("option's seg1:  %s\n",seg1);  
	printf("option's seg2:  %s\n",seg2);  
	printf("option's seg3:  %s\n",seg3);  

	
	printf("argv[1]:  %s\n",argv[1]); 
	printf("argv[2]:  %s\n",argv[2]); 
	printf("argv[3]:  %s\n",argv[3]); 
		
	return 0;
}	
	

