#include <stdio.h>
#include <stdlib.h>

static inline int is_number(float f)
{
    return (f == f);
}

int main()
{
    float a = 100.98;
    float b = 0.0/0.0;
    int c;

    printf("a is %f\n", a);
    printf("b is %f\n", b);
    printf("a is number: %d\n", is_number(a));
    printf("b is number: %d\n", is_number(b));

    c = a;
    printf("c is %d\n", c);
    c = b;
    printf("c is %d\n", c);
    return 0;
}