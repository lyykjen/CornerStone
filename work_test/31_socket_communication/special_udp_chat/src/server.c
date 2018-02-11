/*
 ============================================================================
 Name        : udp.c
 Author      : zhujy
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t   cond = PTHREAD_COND_INITIALIZER ;


struct pthread_sock{
	int server_st;
	struct sockaddr_in addr;
};

void *sendsocket(void *arg)
{
	struct pthread_sock *ps = (struct pthread_sock *)arg;
	char buf[1024];
#if 1	
	struct sockaddr_in caddr;
	memset(&caddr, 0, sizeof(caddr));
	caddr.sin_family = AF_INET;
	caddr.sin_port = htons(14550);//client port
	caddr.sin_addr.s_addr = inet_addr("192.168.20.105");//client ip args[1]
#endif	
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(STDIN_FILENO, buf, sizeof(buf));//读取用户键盘输入				
		if (sendto(ps->server_st, buf, strlen(buf), 0, (struct sockaddr *) &caddr,
				sizeof(caddr)) == -1)//udp使用sendto发送消息
		{
			printf("sendto failed %s\n", strerror(errno));
			break;
		}
	}		
	return NULL;	
}


void *recvsocket(void *arg)
{
	struct pthread_sock *ps = (struct pthread_sock *)arg;
	char buf[1024];
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	
	while(1)
	{
		memset(&client_addr, 0, sizeof(client_addr));
		memset(buf, 0, sizeof(buf));
		if(recvfrom(ps->server_st, buf, sizeof(buf), 0,
				(struct sockaddr *)&client_addr, &len) == -1)
		{
			printf("recvfrom failed %s\n", strerror(errno));
			break;
		}
		else
		{
			printf("receive from %s:%d\n",
					inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			printf(" %s\n", buf);	
		}
	}
	
	return NULL;
}

int main(int arg, char *args[])
{
	if (arg < 1)
		return -1;

	int server_st = socket(AF_INET, SOCK_DGRAM, 0);
	if (server_st == -1)
	{
		printf("socket failed %s\n", strerror(errno));
		return 0;
	}

	//int port = atoi(args[1]);
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(0);//server port
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr(args[1]);
	if (bind(server_st, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)//UDP接收数据，也需要绑定IP
	{
		printf("bind failed %s\n", strerror(errno));
		return -1;
	}
	
	
	
	
	pthread_t thrd1, thrd2;
	
	struct pthread_sock ps;
	ps.server_st = server_st;//服务器的socket(和服务器端口绑定在一起)
	//ps.addr = client_addr;//接收来自客户端的地址信息	
	pthread_create(&thrd2, NULL, sendsocket, &ps);//创建发送线程
	
	char buf[1024];
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	while(1)
	{
		memset(&client_addr, 0, sizeof(client_addr));
		memset(buf, 0, sizeof(buf));
		if(recvfrom(server_st, buf, sizeof(buf), 0,
				(struct sockaddr *)&client_addr, &len) == -1)
		{
			printf("recvfrom failed %s\n", strerror(errno));
			continue;
		}else
		{
			printf("New client: %s:%d\n",
					inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));			
			printf(" %s\n", buf);
			break;//收到客户端地址后立刻退出，让recvsocket线程继续运行
		}
	}
	ps.server_st = server_st;//服务器的socket(和服务器端口绑定在一起)
	ps.addr = client_addr;//接收来自客户端的地址信息	
	pthread_create(&thrd1, NULL, recvsocket, &ps);//创建接收线程


	pthread_join(thrd1, NULL);
	close(server_st);
	return 0;
}
