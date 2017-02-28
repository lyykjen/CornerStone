#include <stdio.h>

struct person {
	char *name;
	char * (*printName)(struct person *per);
};

char * printName(struct person *per)
{
	return per->name;
}

int main(void)
{
	struct person p1 = {"zhangsan", printName};
	struct person p2 = {"lisi", printName};

	//printf("%s\n", p1.name);
	//printf("%s\n", p2.name);
	//p1.printName(&p1);
	//p2.printName(&p2);
	printf("%s\n", p1.printName(&p1));
	printf("%s\n", p2.printName(&p2));
		
	return 0;
}