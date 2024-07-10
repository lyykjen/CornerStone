/*
 Compile: gcc -o test1 test1.c
 Execute: 
		The former:	
					$ ./test1 -a  
					other option :?  
					optopt +a  
					$ ./test1 -b  
					option b :b  
					optopt +  
					$ ./test1 -c  
					other option :c  
					optopt +  
					$ ./test1 -d  
					other option :d  
					optopt +  
					$ ./test1 -abcd  
					option a:'bcd' 
					optopt +  
					$ ./test1 -bcd  
					option b :b  
					other option :c  
					other option :d  
					optopt +  
					$ ./test1 -bcde  
					option b :b  
					other option :c  
					other option :d  
					other option :e  
					optopt +  
					$ ./test1 -bcdef  
					option b :b  
					other option :c  
					other option :d  
					other option :e  
					other option :?
					optopt +f  
						 
		The latter:	./test1 -a aa bb cc 
*/
#if 1
#include <stdio.h>  
#include <unistd.h>  

int main(int argc, char *argv[])  
{  
		int ch;  
		opterr = 0;  
		while ((ch = getopt(argc,argv,"a:bcde"))!=-1)  
		{  
				switch(ch)  
				{  
						case 'a':  
								printf("option a:'%s'\n",optarg);  
								break;  
						case 'b':  
								printf("option b :b\n");  
								break;  
						default:  
								printf("other option :%c\n",ch);  
				}  
		//printf("optopt +%c\n",optopt);  
		}  
		printf("optopt +%c\n",optopt); 
			
}  

#else 

#include <stdio.h>  
#include<unistd.h>  
int main(int argc, char *argv[])  
{  
	int ch;  
	char *seg1,*seg2,*seg3;  
	while((ch = getopt(argc,argv,"a:"))!= -1)  
	{  	
		switch(ch)  
		{  
			case 'a':   
			{  
				seg1=optarg;  
				seg2=argv[optind];  
				seg3=argv[optind+1];  
			}; break;  
			default: printf("unrecongnized option :%c\n",ch);  
		}
		printf("option's seg1:  %s\n",seg1);  
		printf("option's seg2:  %s\n",seg2);  
		printf("option's seg3:  %s\n",seg3);  
	}
		
	return 0;
} 	
		
#endif	
