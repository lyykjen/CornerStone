// 如果要获取进程凭据，则需要打开该宏定义才可以，这个宏定义一定要放在编译最开始
#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <sys/socket.h> // 定义了cred结构体，用于存放进程凭据（pid uid和gid）
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h> // 定义了sockaddr_un结构体

char *server_socket_path="server.socket"; // 这里跟server保持一致

int main()
{
	struct sockaddr_un server_addr;
	int clientfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (clientfd < 0) {
		printf("create socket faield!\n");
		return -1;
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sun_family=AF_UNIX;
	strcpy(server_addr.sun_path, server_socket_path);
	if (connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		printf("connect to server failed!\n");
		close(clientfd);
		return -1;
	}
	close(clientfd);
	return 0;	
}


