#include <stdio.h>

int main(void)
{
int a = 0x12345678;
char *p = (char *)(&a);
if (*p == 0x78) {
printf("Little-Endian!\n");
} else if (*p == 0x12) {
printf("Big-Endian!\n");
} else {
printf("other!\n");
}
return 0;
}
