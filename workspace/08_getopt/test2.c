/*
 Compile: gcc -o test2 test2.c
 Execute: ./test2 -a/dev/ttyS1 -b/tmp/SD0 -c500000
						or 
		  ./test2 -a /dev/ttyS1 -b /tmp/SD0 -c 500000
*/
#include <stdio.h>  
#include <unistd.h>  

int main(int argc, char *argv[])  
{  
		int ch;  
		opterr = 0;  
		char *seg1,*seg2,*seg3; 
		while ((ch = getopt(argc,argv,"a:b:c:"))!=-1)  
		{  
				switch(ch)  
				{  
						case 'a':  
								printf("option a:'%s'\n",optarg);  
								seg1 = optarg;
								break;  
						case 'b':  
								printf("option b:'%s'\n",optarg);   
								seg2 = optarg;								
								break;  
						case 'c':  
								printf("option c:'%s'\n",optarg);  
								seg3= optarg;				
								break;  						
						default:  
								printf("other option :%c\n",ch);  
				}  
				//printf("optopt +%c\n",optopt);  
		}  		
		
		printf("option's seg1:  %s\n",seg1);  
		printf("option's seg2:  %s\n",seg2);  
		printf("option's seg3:  %s\n",seg3);  
			
}  


