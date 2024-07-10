/*
 Compile: gcc -o getopt_long getopt_long.c
 Execute: ./getopt_long -b 500000 -p /dev/ttyS1 -s /tmp/SD0 -V
						or 
		  ./getopt_long --baudrate 50000 --port /dev/ttyS1 --sdpath /tmp/SD0 --version
*/
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <getopt.h>
#include <string.h>
		
static void usage()
{
   fprintf(stderr,
	"zaver [option]... \n"
	"  -b|--baudrate <baudrate value>   Specify baudrate.\n"
	"  -p|--port <serial port num>      Specify serial port device number.\n"
	"  -h                               Display program usage.\n"
	"  -V|--version                     Display program version.\n"
	);
}

static struct option long_options[] = {
           {"baudrate", required_argument, NULL, 'b'},
           {"port", required_argument, NULL, 'p'},          
           {"sdpath", required_argument, NULL, 's'},
           {"help", no_argument, NULL,  'h'},
           {"version", no_argument, NULL,  'V' },
           {0,         0,                 0,  0 }
       };
		
	
const char *optstring = "b:p:s:hV";  
		
int main(int argc, char *argv[])  
{  
		if (argc == 1)
		{
	        usage();
	        return 0;
    	}

		int ch,baudrate_value = 0;  
		int option_index = 0; 
		unsigned char *port = NULL,*baudrate = NULL,*SDPath = NULL; 
		while ((ch = getopt_long(argc, argv, optstring, long_options, &option_index))!= -1)
		{  
			printf("option's ch:  %c\n",ch);
			printf("option's optind:  %d\n",optind);   		
			switch(ch)  
			{  
					case 'b': 
							baudrate = optarg;
							printf("option's baudrate:  %s\n",baudrate); 									
							break;  
					case 'p':  	
							if (optarg)                                
								port = optarg;
							printf("option's port:  %s\n",port); 							
							break;  
					case 's':  
							if (optarg)	
							SDPath= optarg;	
							printf("option's SDPath:  %s\n",SDPath);			
							break;					
					case 'V':
							printf("ync_ser2net's version: E90_0.6.08_A\n");
							break;
					case 'h':
							usage();
							break;
					default:
							usage();
							return 0;
     
			}  	
		} 
		
		if( optind < 3)
		{
			printf("baudrate setting err!");		
			return -1;
		}	
		else
		{
			baudrate_value = atoi(baudrate);
			printf("use %d baudrate\n",baudrate_value);
		}
		
		if( (optind < 5)||(strncasecmp(port,"/dev/ttyS",9)!=0))
		{
			printf("use default /dev/ttyS2 port\n");
			return -1;
		}	
		else	
		{
			printf("use %s port\n",port);
		}	
			
		printf("option's baudrate:  %s\n",baudrate);  
		printf("option's port:  %s\n",port);  
		printf("option's SDPath:  %s\n",SDPath);  
		return 0;
}  
