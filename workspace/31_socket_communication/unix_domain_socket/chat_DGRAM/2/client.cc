#include <string.h>
#include <zconf.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>

#define BUF_SIZE 1024             /* Maximum size of messages exchanged between client and server */
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
    /* Create client socket; bind to unique pathname (based on PID) */
    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&claddr, 0, sizeof(struct sockaddr_un));
    claddr.sun_family = AF_UNIX;
    snprintf(claddr.sun_path, sizeof(claddr.sun_path),
            "unix.socket.%ld", (long) getpid());
    remove(claddr.sun_path); 

    if (bind(sfd, (struct sockaddr *) &claddr, sizeof(struct sockaddr_un)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    /* Construct address of server */

    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);


    struct pthread_sock ps;
    ps.st = sfd;//客户端的socket
    ps.addr = svaddr;//服务器信息


    /* Send messages to server; echo responses on stdout */

    pthread_t thrd1, thrd2;
    pthread_create(&thrd1, NULL, recvsocket, &ps);
    pthread_create(&thrd2, NULL, sendsocket, &ps);

    pthread_join(thrd1, NULL);


    remove(claddr.sun_path);            /* Remove client socket pathname */
    close(sfd);
    exit(EXIT_SUCCESS);
}
