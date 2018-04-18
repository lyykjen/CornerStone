#include <stdio.h>
#include <signal.h>

typedef void (* signal_handler)(int);

void signal_handler_fun(int signal_num)
{
	printf("catch signal %d\n", signal_num);
}

int main(int argc, char *argv[])
{
	signal_handler p_signal = signal_handler_fun;
	signal(SIGINT, p_signal);
	while(1);
	return 0;
}