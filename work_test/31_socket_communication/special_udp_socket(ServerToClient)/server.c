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
	saddr.sin_port = htons(0);//port
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(server_st, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)//UDP接收数据，也需要绑定IP
	{
		printf("bind failed %s\n", strerror(errno));
		return -1;
	}
	//char buf[1024];
	//struct sockaddr_in client_addr;
	//socklen_t len = sizeof(client_addr);
#if 1

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(14550);//client port
	addr.sin_addr.s_addr = inet_addr(args[1]);//client ip
	char buf[1024];
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(STDIN_FILENO, buf, sizeof(buf));//读取用户键盘输入
		if (sendto(server_st, buf, strlen(buf), 0, (struct sockaddr *) &addr,
				sizeof(addr)) == -1)//udp使用sendto发送消息
		{
			printf("sendto failed %s\n", strerror(errno));
			break;
		}
	}
#endif	
#if 0	
	while(1)
	{
		memset(&client_addr, 0, sizeof(client_addr));
		memset(buf, 0, sizeof(buf));
		if(recvfrom(server_st, buf, sizeof(buf), 0,
				(struct sockaddr *)&client_addr, &len) == -1)
		{
			printf("recvfrom failed %s\n", strerror(errno));
			break;
		}else
		{

			printf("%s recv is %s\n", inet_ntoa(client_addr.sin_addr), buf);
		}
	}
#endif	
	close(server_st);
	return 0;
}
