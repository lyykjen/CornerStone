/* 用read代替scanf的一种用法 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#define STD_INPUT 0  
#define STD_OUTPUT 1  
#define STD_ERROR 2
int main()
{
	char cmd[256];
	int num,Len,len;
	int var = 0x00;
	var += 400;
	printf("var = %02x\n",var);
	while(1)
	{
		//memset(cmd,0,sizeof(cmd));
#if 0		
		scanf("%s",cmd);
#else
		//fgets(cmd,strlen(cmd),stdin);
		//printf("cmd = %s,len = %d\n",cmd,(int)strlen(cmd));
		Len = read(STDIN_FILENO,cmd,sizeof(cmd)); //Len为read成功读取的字节数，包括最后的回车符'\n'
	
		if(Len==-1)  
		{  
			write(STD_ERROR,"error\n",6);  
			exit(0);  
		}  
		printf("cmd[Len-1] = %d\n",cmd[Len-1]);//打印该字符的ASCII码，就是回车符号的ASCII码
		cmd[Len-1] = '\0';//将最后的回车符号换成字符串结束符'\0'
		//write(STDOUT_FILENO, cmd, 256);
		
#endif		
		num = (!strcasecmp(cmd,"123abc"))?4: 
							((!strcasecmp(cmd,"qwe"))?3:	
							((!strcasecmp(cmd,"123"))?2:
							((!strcasecmp(cmd,"abc"))?1: 0 )));
		write(STDOUT_FILENO,cmd,Len);//将cmd中内容输出到屏幕，输出内容长度为Len	
		printf("\n");		
		printf("num = %d\n",num);
	}
	
	//puts(cmd);
	return 0;
}
