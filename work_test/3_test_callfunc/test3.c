#include<stdio.h>

// 方法指针的格式为：int (*ptr)(char *p) 即：返回值(指针名)(参数列表)
typedef int (*CallBackFun)(char *p); // 为回调函数命名，类型命名为 CallBackFun，参数为char *p

int Afun(char *p) {    // 方法 Afun，格式符合 CallBackFun 的格式，因此可以看作是一个 CallBackFun
    printf("Afun 回调打印出字符%s!\n", p);
    return 0;
}

int Cfun(char *p) {    // 方法 Cfun，格式符合 CallBackFun 的格式，因此可以看作是一个 CallBackFun
    printf("Cfun 回调打印:%s, Nice to meet you!\n", p);
    return 0;
}

int call(CallBackFun pCallBack, char *p) { // 执行回调函数，方式一：通过命名方式
    printf("call 直接打印出字符%s!\n", p);
    pCallBack(p);
    return 0;
}

// int call2(char *p, int (*ptr)(char *p)) 
int call2(char *p, int (*ptr)()) { // 执行回调函数，方式二：直接通过方法指针
    printf("==============\n"); 
    (*ptr)(p); 
}

int call3(char *p, CallBackFun pCallBack){ // 执行回调函数，方式一：通过命名方式
    printf("--------------\n");
    pCallBack(p); 
}

int main() {    

    char *p = "hello";

    call(Afun, p);
    call(Cfun, p);

    call2(p, Afun);
    call2(p, Cfun);

    call3(p, Afun);
    call3(p, Cfun);

    // int i = getchar();
    // printf("Input: %c \n", i);

    return 0;
}