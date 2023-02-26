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
int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd, cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    // 创建一个 socket。
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }


    if (strlen(SV_SOCK_PATH) > sizeof(addr.sun_path) - 1){
        printf("Server socket path too long: %s", SV_SOCK_PATH);
        exit(EXIT_FAILURE);
    }

    // 删除所有与路径名一致的既有文件，这样才能将 socket 绑定到这个路径名上
    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT){
        printf("remove-%s", SV_SOCK_PATH);
        exit(EXIT_FAILURE);
    }


    //为服务器 socket 构建一个地址结构
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    //将 socket 绑定到该地址上
    if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
    {
        printf("bind");
        exit(EXIT_FAILURE);
    }

    // 将这个 socket 标记为监听 socket。
    if (listen(sfd, BACKLOG) == -1){
        printf("listen");
        exit(EXIT_FAILURE);
    }

    // 执行一个无限循环来处理进入的客户端请求。每次循环迭代执行下列任务。
    for (;;) {          /* Handle client connections iteratively */

        /* Accept a connection. The connection is returned on a new
           socket, 'cfd'; the listening socket ('sfd') remains open
           and can be used to accept further connections. */
        // 接受一个连接，为该连接获取一个新 socket cfd。
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1)
        {
            printf("accept");
            exit(EXIT_FAILURE);
        }

        /* Transfer data from connected socket to stdout until EOF */
        //从已连接的 socket 中读取所有数据并将这些数据写入到标准输出中。
        while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)

            if (write(STDOUT_FILENO, buf, numRead) != numRead)
            {
                printf("partial/failed write");
                exit(EXIT_FAILURE);
            }

        if (numRead == -1)
        {
            printf("read");
            exit(EXIT_FAILURE);
        }

        // 关闭已连接的 socket cfd
        if (close(cfd) == -1)
        {
            printf("close");
            exit(EXIT_FAILURE);
        }
    }
}

