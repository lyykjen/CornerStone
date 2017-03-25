/*
 Compile: gcc -o test2 test2.c
 Execute: ./test3 -a500000 -b/dev/ttyS1 -c/tmp/SD0
						or 
		  ./test3 -a 500000 -b /dev/ttyS1 -c /tmp/SD0
*/
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>

#define USAGE                                       \
        {                                           \
           fprintf( stderr,                         \
                    "Usage: ync_ser2net -abaudrate [-bport] [-cSDPath] \n" );\
           exit(1);                             \
        } 
		
#define ROOTPATH "/home/lyy/test"
#define VP ROOTPATH"/gimbal.yuneec"
		
	
		
int main(int argc, char *argv[])  
{  
		int ch,baudrate_value = 0;  
		//opterr = 0;  
		unsigned char *port = NULL,*baudrate = NULL,*SDPath = NULL; 
		while ((ch = getopt(argc,argv,"a:b::c::"))!=-1)  
		{  
			printf("option's ch:  %c\n",ch);  		
				switch(ch)  
				{  
						case 'a': 
								baudrate = optarg;									
								break;  
						case 'b':  	
								if (optarg)                                
									port = optarg;								
								break;  
						case 'c':  
								if (optarg)	
								SDPath= optarg;				
								break; 
						default:
								USAGE;
         
				}  
				
		} 
		if( optind < 2)
		{
			perror("baudrate setting err!\n");		
			return -1;
		}	
		else
		{
			baudrate_value = atoi(baudrate);
			printf("use %d baudrate\n",baudrate_value);
		}
		
		if( (optind < 3)||(strncasecmp(port,"/dev/ttyS",9)!=0))
		{
			printf("use default /dev/ttyS2 port\n");
			//udp_uart_fd.fd = uart1_init("/dev/ttyS2");
		}	
		else	
		{
			printf("use %s port\n",port);
			//udp_uart_fd.fd = uart1_init(argv[2]);
		}	
		
		printf("VP = %s\n",VP);
		printf("option's ch:  %d\n",ch);
		printf("option's optind:  %d\n",optind);  		
		printf("option's baudrate:  %s\n",baudrate);  
		printf("option's port:  %s\n",port);  
		printf("option's SDPath:  %s\n",SDPath);  
		printf("baudrate_value:  %d\n",baudrate_value);
		//printf("argc:  %d\n",argc);
			
}  
