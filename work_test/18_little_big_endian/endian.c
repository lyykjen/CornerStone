#include <stdio.h>

int main(void)
{
int a = 0x12345678;
char *p = (char *)(&a);
if (*p == 0x78) {
printf("xiao duan!\n");
} else if (*p == 0x12) {
printf("da duan!\n");
} else {
printf("other!\n");
}
return 0;
}
