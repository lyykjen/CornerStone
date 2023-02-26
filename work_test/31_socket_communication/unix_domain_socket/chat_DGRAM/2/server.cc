// us_xfr.h
#include <string.h>
#include <zconf.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>

#define BUF_SIZE 1024             /* Maximum size of messages exchanged
                                   between client and server */
#define SV_SOCK_PATH "unix.socket"

struct pthread_sock{
    int st;
    struct sockaddr_un addr;
};

void *recvsocket(void *arg)
{
    struct pthread_sock *ps = (struct pthread_sock *)arg;
    
    char buf[1024];
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        if(recvfrom(ps->st, buf, sizeof(buf), 0, NULL, NULL) == -1)
        {
            printf("recvfrom failed %s\n", strerror(errno));
            break;
        }else
        {
            printf("receive from %s\n", ps->addr.sun_path);
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
        if (sendto(ps->st, buf, strlen(buf), 0, (struct sockaddr *)&(ps->addr),
                sizeof(ps->addr)) == -1)//udp使用sendto发送消息
        {
            printf("sendto failed %s\n", strerror(errno));
            break;
        }
    }
        
    return NULL;    
}

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr, claddr;
    int sfd;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];

  // 先创建一个 socket
    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);       /* Create server socket */
    if (sfd == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }


    if (strlen(SV_SOCK_PATH) > sizeof(svaddr.sun_path) - 1){
         printf("Server socket path too long: %s", SV_SOCK_PATH);
         exit(EXIT_FAILURE);
     }

   //服务器先删除了与该地址匹配的路径名，以防出现这个路径名已经存在的情况
    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT){
         printf("remove-%s", SV_SOCK_PATH);
         exit(EXIT_FAILURE);
	}
	// 将其绑定到一个众所周知的地址上
    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

    if (bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1)
    {
        printf("bind");
        exit(EXIT_FAILURE);
    }

    /* Receive messages, convert to uppercase, and return to client */

    for (;;) {
        len = sizeof(struct sockaddr_un);
        numBytes = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
        if (numBytes == -1) {
        	perror("recvfrom");
            sleep(1);
        	continue;
    	}else{
            printf("receive from %s\n", claddr.sun_path);
            printf(" %s\n", buf);
            break;
        }
    }


    struct pthread_sock ps;
    ps.st = sfd;//服务端的socket
    ps.addr = claddr;//客户端信息

    pthread_t thrd1, thrd2;
    pthread_create(&thrd1, NULL, recvsocket, &ps);
    pthread_create(&thrd2, NULL, sendsocket, &ps);

    pthread_join(thrd1, NULL);
    close(sfd);
    return 0;
}
