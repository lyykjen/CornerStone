// us_xfr.h
#include <string.h>
#include <zconf.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BACKLOG 5
#define SV_SOCK_PATH "unix.socket"
#define BUF_SIZE 100
int
main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    // 创建一个 socket。
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);      /* Create client socket */
    if (sfd == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Construct server address, and make the connection */
    // 为服务器 socket 构建一个地址结构并连接到位于该地址处的 socket。
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (connect(sfd, (struct sockaddr *) &addr,
                sizeof(struct sockaddr_un)) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    /* Copy stdin to socket */
    //执行一个循环将其标准输入复制到 socket 连接上。当遇到标准输入中的文件结尾时客
    // 户端就终止，其结果是客户端 socket 将会被关闭并且服务器在从连接的另一端的
    // socket 中读取数据时会看到文件结束。
    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
        if (write(sfd, buf, numRead) != numRead)
        {
            printf("partial/failed write");
            exit(EXIT_FAILURE);
        }

    if (numRead == -1)
    {
        printf("read");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);         /* Closes our socket; server sees EOF */
}
