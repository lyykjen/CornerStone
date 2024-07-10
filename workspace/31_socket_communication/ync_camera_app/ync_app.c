/*
 ============================================================================
 Name        : server.c
 Author      : lyy
 Version     :
 Copyright   : Your copyright notice
 Description : Socket in C, Ansi-style
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

#include "mavlink2/common/mavlink.h"

pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t   cond = PTHREAD_COND_INITIALIZER ;


struct pthread_sock{
	int st;
	struct sockaddr_in addr;
};


void mavlink_parse_and_output_heartbeat(int recv_len, char buf[])
{
	mavlink_message_t msg;
	mavlink_status_t status;
	for (int i = 0; i < recv_len; ++i)
	{	
		int ret = mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status);
		if(ret == 1)
		{
			if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT)
			{
				mavlink_heartbeat_t stHeartBeat;
				mavlink_msg_heartbeat_decode(&msg, &stHeartBeat);
				// Don't change compid, otherwise ground stations tend to get confused.
				mavlink_msg_heartbeat_encode(msg.sysid, msg.compid, &msg, &stHeartBeat);
				printf("uart to udp heartbeat: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n",
							msg.sysid, msg.compid, msg.len, msg.msgid);

			}
		}
		
	}
}

void *sendsocket(void *arg)
{
	struct pthread_sock *ps = (struct pthread_sock *)arg;
	char buf[2048];
	
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(STDIN_FILENO, buf, sizeof(buf));//读取用户键盘输入				
		if (sendto(ps->st, buf, strlen(buf), 0, (struct sockaddr *) &(ps->addr),
				sizeof(ps->addr)) == -1)//udp使用sendto发送消息
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
	char buf[2048];
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	
	while(1)
	{
		memset(&client_addr, 0, sizeof(client_addr));
		memset(buf, 0, sizeof(buf));
		int recv_len = recvfrom(ps->st, buf, sizeof(buf), 0,
				(struct sockaddr *)&client_addr, &len);
		if( recv_len == -1)
		{
			printf("recvfrom failed %s\n", strerror(errno));
			break;
		}
		else
		{
			printf("receive from %s:%d\n",
					inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			mavlink_parse_and_output_heartbeat(recv_len,buf);
			
			printf("received %d from the camera:\n", recv_len);
			for (int i = 0; i < recv_len; i++)
			{
				printf("%02x ", (unsigned char)buf[i]);
			}
			printf("\n ");
		}
	}
	
	return NULL;
}

int main(int arg, char *args[])
{
	if (arg < 1)
		return -1;

	int st = socket(AF_INET, SOCK_DGRAM, 0);
	if (st == -1)
	{
		printf("socket failed %s\n", strerror(errno));
		return 0;
	}

	//int port = atoi(args[1]);
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(14550);//client port(模拟遥控器)
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(st, (struct sockaddr *)&addr, sizeof(addr)) == -1)//UDP接收数据，也需要绑定IP
	{
		printf("bind failed %s\n", strerror(errno));
		return -1;
	}
	
	char buf[1024];
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	
	while(1)
	{
		memset(&client_addr, 0, sizeof(client_addr));
		memset(buf, 0, sizeof(buf));
		int recv_len = recvfrom(st, buf, sizeof(buf), 0,(struct sockaddr *)&client_addr, &len);
		if(recv_len == -1)
		{
			printf("recvfrom failed %s\n", strerror(errno));
			continue;
		}else
		{
			printf("New client: %s:%d\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));	
			
			mavlink_parse_and_output_heartbeat(recv_len, buf);
			
			break;//收到客户端地址后立刻退出，让recvsocket线程继续运行
		}
	}
	
	pthread_t thrd1, thrd2;
	
	struct pthread_sock ps;
	ps.st = st;//服务器的socket(和服务器端口绑定在一起)
	ps.addr = client_addr;//接收来自客户端的地址信息				
	pthread_create(&thrd1, NULL, recvsocket, &ps);
	pthread_create(&thrd2, NULL, sendsocket, &ps);

	pthread_join(thrd1, NULL);
	close(st);
	return 0;
}
