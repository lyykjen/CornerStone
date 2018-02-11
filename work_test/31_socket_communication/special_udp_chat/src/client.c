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

struct pthread_sock{
	int client_st;
	struct sockaddr_in addr;
};

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
		if(recvfrom(ps->client_st, buf, sizeof(buf), 0,
				(struct sockaddr *)&client_addr, &len) == -1)
		{
			printf("recvfrom failed %s\n", strerror(errno));
			break;
		}else
		{

			printf("receive from %s:%d\n",
					inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			printf(" %s\n", buf);	
		}
	}
	
	return NULL;
}

void *sendsocket(void *arg)
{
	struct pthread_sock *ps = (struct pthread_sock *)arg;
	char buf[1024];
	
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(STDIN_FILENO, buf, sizeof(buf));//读取用户键盘输入
		if (sendto(ps->client_st, buf, strlen(buf), 0, (struct sockaddr *)&(ps->addr),
				sizeof(ps->addr)) == -1)//udp使用sendto发送消息
		{
			printf("sendto failed %s\n", strerror(errno));
			break;
		}
	}
		
	return NULL;	
}


int main(int arg, char *args[])
{
	if (arg < 2)
	{
		printf("Usage:./udp target_IP\n");
		return -1;
	}

	int client_st = socket(AF_INET, SOCK_DGRAM, 0);//建立socket的时候第二个参数值为SOCK_DGRAM
	if (client_st == -1)
	{
		printf("socket failed %s\n", strerror(errno));
		return 0;
	}

	//int port = atoi(args[2]);


	int on = 1;
	if (setsockopt(client_st, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) == -1)//设置UDP socket可以发送广播消息
	{
		printf("setsockopt failed %s\n", strerror(errno));
		return EXIT_FAILURE;
	}



	struct sockaddr_in caddr;
	memset(&caddr, 0, sizeof(caddr));
	caddr.sin_family = AF_INET;
	caddr.sin_port = htons(14550);//port
	caddr.sin_addr.s_addr = inet_addr(args[1]);//htonl(INADDR_ANY);
	

	struct pthread_sock ps;
	pthread_t thrd1, thrd2;
#if 1	
	if (bind(client_st, (struct sockaddr *)&caddr, sizeof(caddr)) == -1)//UDP接收数据，也需要绑定IP
	{
		printf("bind failed %s\n", strerror(errno));
		return -1;
	}
	
	char buf[1024];
	struct sockaddr_in server_addr;
	socklen_t len = sizeof(server_addr);
	while(1)
	{
		memset(&server_addr, 0, sizeof(server_addr));
		memset(buf, 0, sizeof(buf));
		if(recvfrom(client_st, buf, sizeof(buf), 0,
				(struct sockaddr *)&server_addr, &len) == -1)
		{
			printf("recvfrom failed %s\n", strerror(errno));
			continue;
		}else
		{
			printf("New client: %s:%d\n",
					inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));			
			printf(" %s\n", buf);
			break;//收到客户端地址后立刻退出，让recvsocket线程继续运行
		}
	}
	
#endif	

	
	
	

	ps.client_st = client_st;//客户端的socket
	ps.addr = server_addr;//服务器的IP和端口号
	pthread_create(&thrd1, NULL, recvsocket, &ps);
	pthread_create(&thrd2, NULL, sendsocket, &ps);
	
/*	
	char buf[1024];
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(STDIN_FILENO, buf, sizeof(buf));//读取用户键盘输入
		if (sendto(client_st, buf, strlen(buf), 0, (struct sockaddr *) &addr,
				sizeof(addr)) == -1)//udp使用sendto发送消息
		{
			printf("sendto failed %s\n", strerror(errno));
			break;
		}
	}
*/	
	pthread_join(thrd1, NULL);
	close(client_st);
	return EXIT_SUCCESS;
}

