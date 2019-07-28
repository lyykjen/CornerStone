#include <stdio.h>
#include <stdint.h>
//#include "method.h"

template<typename  T> void swap(T& t1, T& t2) {
    printf("sizeof(T) = %lu\n",sizeof(T));
    T tmpT;
    tmpT = t1;
    t1 = t2;
    t2 = tmpT;
}

int main() {
    //模板方法 
    int num1 = 1, num2 = 2;
    swap(num1, num2);
    printf("num1:%d, num2:%d\n", num1, num2); 

    uint64_t num3 = 8888, num4 = 6666;
    swap(num3, num4);
    printf("num3:%lu, num4:%lu\n", num3, num4);
    return 0;
}
