/*
    Taken from http://www.cnblogs.com/life2refuel/p/7154961.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define CERR(fmt, ...) \
    fprintf(stderr, "[%s:%s:%d][errno %d:%s]" fmt "\n",\
        __FILE__, __func__, __LINE__, errno, strerror(errno), ##__VA_ARGS__)

#define CERR_EXIT(fmt,...) \
    CERR(fmt, ##__VA_ARGS__), exit(EXIT_FAILURE)

#define CERR_IF(code) \
    if((code) < 0) \
        CERR_EXIT(#code)

//待拼接的字符串
#define _STR_HTTPBEG "GET /index.html HTTP/1.0\r\nUser-Agent: Happy is good.\r\nHost: 127.0.0.1:"
#define _STR_HTTPEND "\r\nConnection: close\r\n\r\n"

// 简单请求一下
int main(int argc, char * argv[]) {
    int sfd;
    int len, port;
    char buf[BUFSIZ];
    struct sockaddr_in saddr = { AF_INET };

    // argc 默认为1 第一个参数 就是 执行程序串
    if((argc != 2) || (port = atoi(argv[1])) <= 0 )
        CERR_EXIT("Usage: %s [port]", argv[0]);
    
    // 开始了,就这样了    
    CERR_IF(sfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP));
    saddr.sin_port = htons(port);
    CERR_IF(connect(sfd, (struct sockaddr *)&saddr, sizeof saddr));
    
    //开始发送请求
    strcpy(buf, _STR_HTTPBEG);
    strcat(buf, argv[1]);
    strcat(buf, _STR_HTTPEND);
    write(sfd, buf, strlen(buf));

    //读取所哟内容
    while((len = read(sfd, buf, sizeof buf - 1)) > 0) {
        buf[len] = '\0';
        printf("%s", buf);    
    }
    putchar('\n');    

    close(sfd);
    return EXIT_SUCCESS;
}
