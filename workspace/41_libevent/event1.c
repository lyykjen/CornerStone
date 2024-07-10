/*
	Taken from https://blog.csdn.net/jason___bourne/article/details/46732041
*/

#include <sys/signal.h>
#include <event.h>

struct event_base* base = NULL;
struct event* signal_event = NULL;
struct event* timeout_event = NULL;
struct timeval tv = {0,0};

void signal_cb (int fd, short event, void* argc)//信号回调函数
{
        struct event_base* base = (struct event_base*) argc;//获取传递进来的Reactor对象
        struct timeval delay = { 2,0};//设置延时结构体，延时时间2s
        printf("Caught an interrupt signal; exciting cleanly in two seconds...\n");
        event_base_loopexit (base,&delay);
}

void timeout_cb (int fd,short event, void* argc)
{
        printf("Hello Libevent!\n");
        event_add(timeout_event,&tv);
}

int main()
{
        struct event_base* base = event_init();//生成Reactor实例

        signal_event = evsignal_new(base,SIGINT,signal_cb,base);//生成SIGINT信号的事件处理器
        event_add(signal_event,NULL);//将事件处理器加入到注册事件队列

        tv.tv_sec = 1;
        tv.tv_usec = 0;
        timeout_event = evtimer_new(base,timeout_cb,NULL);//生成定时器处理器
        event_add(timeout_event,&tv);//将定时器处理器加入注册事件队列

        event_base_dispatch(base);//分发事件

        event_free(timeout_event);
        event_free(signal_event);
        event_base_free(base);
}                              