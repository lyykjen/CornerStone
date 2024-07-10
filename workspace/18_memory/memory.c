#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void GetMemory0(char *p)  
{  
	p = (char *)malloc(100); /*p是局部变量,GetMemory0执行结束后p自动消失*/
}  
void Test1(void)  
{  
	char *str = NULL;  
	GetMemory0(str);  
	strcpy(str, "hello world"); 
	/*运行上一句时程序崩溃，因为GetMemory0（char *p）不能传递动态内存,原因是GetMemory0（str)的参数是值传递，不会改变str的值*/  
	printf("%s\n",str);   
}  
char *GetMemory1(void)  
{  
	char p[] = "hello world"; 
#if 0//解决方法
	//static char p[] = "hello world"; 
	char *p = (void *)malloc(100); 
	strcpy(p, "hello world");	
#endif	
	return p;  
}  
void Test2(void)  
{  
	char *str = NULL;  
	str = GetMemory1();  	
	printf("%s\n",str);  
	/*乱码，*GetMemory1()返回的是栈指针，在函数结束时已经栈退解，内容未知*/ 
	free(str);	
}  
void GetMemory2(char **p, int num)  
{  
	*p = (char *)malloc(num);  
}  
void Test3(void)  
{  
	char *str = NULL;  
	GetMemory2(&str, 100);  
	strcpy(str, "hello");  
	/*能正确输出"hello",但有一个问题，内存泄露，malloc的内存没有free*/  
	printf("%s\n",str);  
}  
void Test4(void)  
{  
	char *str = (char *)malloc(100);  
	strcpy(str, "hello");  
	free(str);    
	if (str == NULL)  
	{  
		strcpy(str, "world");  
		printf("%s\n",str);   
	}  
	/*可以输出"world",因为free之后str变为了野指针，但是并没有置为NULL，因此还会继续执行下面的内容*/  
}  

int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();	
}

/*
解决方法：
Test1:
	void GetMemory0(char **p)  
	{  
		*p = (char *)malloc(100); 
	}  
	void Test1(void)  
	{  
		char *str = NULL;  
		GetMemory0(&str);  
		strcpy(str, "hello world"); 	
		printf("%s\n",str);   
	} 
Test2:	
	char *GetMemory1(void)  
	{  	
		//static char p[] = "hello world"; //添加static也是一个方法
		char *p = (void *)malloc(100); //分配malloc内存地址，属于堆空间
		strcpy(p, "hello world");//也可以放到Test2函数中	
		return p;  
	}  
	void Test2(void)  
	{  
		char *str = NULL;  
		str = GetMemory1();  	
		printf("%s\n",str);  	
		free(str);	//malloc分配的内存一定要free掉
	}
Test3:	
	在Test3函数最后添加free(str)
Test4:
	void Test4(void)  
	{  
		char *str = (char *)malloc(100);  
		strcpy(str, "hello");  	   
		if (str != NULL)  
		{  
			strcpy(str, "world");  
			printf("%s\n",str);   
		}
		free(str);	
	} 
*/