#include<stdio.h>

typedef struct person {
	char *dest;
	void (*PrintFunc)(struct person *arg);
	
}per,*p;

/*void printName1(char *arg)
{
	printf("%s\n",arg);
}*/

void printName(p arg)
{
	printf("%s\n",arg->dest);
}

int main(int argc,char **argv)
{
	per Lin = {"Nanjing",printName};
	printf("Lin.dest = %s\n",Lin.dest);
	//Lin.PrintFunc1(Lin.dest);
	Lin.PrintFunc(&Lin);
	
}