// 如果要获取进程凭据，则需要打开该宏定义才可以，这个宏定义一定要放在编译最开始
#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif
#include <sys/socket.h> // 定义了cred结构体，用于存放进程凭据（pid uid和gid）
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/un.h> // 定义了sockaddr_un结构体


char *server_socket_path = "server.socket"; // 在server运行目录生成socket文件用于接收client发来的消息

int main()
{
	struct sockaddr_un server_addr;
	int listenfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (listenfd < 0) {
		printf("create socket failed\n");
		return -1;
	}
	
	memset(&server_addr, 0, sizeof(server_addr));
	strcpy(server_addr.sun_path, server_socket_path); // 初始化socket文件路径
	unlink(server_socket_path); // 一定要删除掉旧文件重新创建，否则会报错
	server_addr.sun_family=AF_UNIX; // 初始化socket family为AF_UNIX，使用本地IPC模式
	if (bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		close(listenfd);
		return -1;
	}
	if (listen(listenfd, 128) < 0) { // 最大支持连接128个client
		close(listenfd);
		return -1;
	}
	
	int connfd;
	struct sockaddr_un client_addr;
	int msglen;
	while (1) { // 循环监听，等待client连接
		printf("[*] waiting for client connecting\n");
		if ((connfd = accept(listenfd, (struct sockaddr *)&client_addr, (socklen_t*)&msglen)) < 0) {
			continue;
		}
		struct ucred cred; // 保存client的pid uid和gid
		socklen_t len = sizeof(struct ucred);
		getsockopt(connfd, SOL_SOCKET, SO_PEERCRED, &cred, &len);
		printf("[*] Credentials from SO_PEERCRED: pid=%d, uid=%d, gid=%d\n", cred.pid    , cred.uid, cred.gid);
		printf("[*] close connect\n");
		close(connfd);
	}
	close(listenfd);
	return 0;
}
