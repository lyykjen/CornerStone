/*
    Taken from http://www.cnblogs.com/life2refuel/p/7154961.html
    Note: chmod +x index.html
*/

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
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

//
// getfdline - 读取文件描述符 fd 一行的内容,保存在buf中,返回读取内容长度 
// fd        : 文件描述符
// buf        : 保存的内容
// sz        : buf 的大小
// return    : 返回读取的长度
//
int getfdline(int fd, char buf[], int sz);

// 返回400 请求解析失败, 客户端代码错误
void response_400(int cfd);
// 返回404 文件内容, 请求文件没有找见
void response_404(int cfd);
// 返回501 错误, 不支持的请求
void response_501(int cfd);
// 服务器内部错误,无法处理等
void response_500(int cfd);
// 返回200 请求成功 内容, 后面可以加上其它参数,处理文件输出
void response_200(int cfd);
// 服务器返回请求的文件内容
void response_file(int cfd, const char * path);

//
// request_start - 启动一个httpd监听端口, 使用随机端口
// pport     : 输出参数和输出参数, 如果传入NULL, 将不返回自动分配的端口
// return    : 返回启动的文件描述符
//
int request_start(uint16_t * pport);

// 在客户端链接过来, pthread 多线程处理的函数
void * request_accept(void * arg);

//
// request_cgi - 处理客户端的http请求.
// cfd        : 客户端文件描述符
// path        : 请求的文件路径
// type        : 请求类型,默认是POST,其它是GET
// query    : 请求发送的过来的数据, url ? 后面那些数据
// return    : void
//
void request_cgi(int cfd, const char * path, const char * type, const char * query);

//
// 主逻辑,启动服务,可以做成守护进程.
// 具体的实现逻辑, 启动小型玩乐级别的httpd 服务
//
int main(int argc, char * argv[]) {
    uint16_t port = 0;
    if(argc > 1){
        port = atoi(argv[1]);
    }
    pthread_attr_t attr;
    int sfd = request_start(&port);
    
    printf("httpd running on port %u.\n", port);
    // 初始化线程属性
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    for(;;){
        pthread_t tid;
        int cfd = accept(sfd, NULL, NULL);
        if(cfd < 0){
            CERR("accept sfd = %d is error!", sfd);
            break;
        }
        if(pthread_create(&tid, &attr, request_accept, (void *)cfd) < 0)
            CERR("pthread_create run is error!");
    }
    // 销毁吧, 一切都结束了
    pthread_attr_destroy(&attr);
    close(sfd);
    return EXIT_SUCCESS;
}

int 
getfdline(int fd, char buf[], int sz) {
    char c, * tp = buf;
    
    --sz;
    while((tp-buf)<sz){
        if(read(fd, &c, 1) <= 0) //伪造结束条件
            break;
        if(c == '\r'){ //全部以\r分割
            if(recv(fd, &c, 1, MSG_PEEK)>0 && c == '\n')
                read(fd, &c, 1);
            else //意外的结束,填充 \n 结束读取
                *tp++ = '\n';
            break;
        }
        *tp++ = c;
    }
    *tp = '\0';
    return tp - buf;
}

inline void 
response_400(int cfd) {
    const char * estr = 
    "HTTP/1.0 400 BAD REQUEST\r\n"
    "Server: wz simple httpd 1.0\r\n"
    "Content-Type: text/html\r\n"
    "\r\n"
    "<p>你的请求有问题,请检查语法!</p>\r\n";
    
    write(cfd, estr, strlen(estr));
}

inline void 
response_404(int cfd) {
    const char * estr = 
    "HTTP/1.0 404 NOT FOUND\r\n"
    "Server: wz simple httpd 1.0\r\n"
    "Content-Type: text/html\r\n"
    "\r\n"
    "<html>"
    "<head><title>你请求的界面被查水表了!</title></head>\r\n"
    "<body><p>404: 估计是回不来了</p></body>"
    "</html>";
    
    write(cfd, estr, strlen(estr));
}

inline void 
response_501(int cfd) {
    const char * estr = 
    "HTTP/1.0 501 Method Not Implemented\r\n"
    "Server: wz simple httpd 1.0\r\n"
    "Content-Type: text/html\r\n"
    "\r\n"
    "<html>"
    "<head><title>小伙子不要乱请求</title></head>\r\n"
    "<body><p>too young too simple, 年轻人别总想弄出个大新闻.</p></body>"
    "</html>";
    
    write(cfd, estr, strlen(estr));
}

inline void 
response_500(int cfd) {
    const char * estr = 
    "HTTP/1.0 500 Internal Server Error\r\n"
    "Server: wz simple httpd 1.0\r\n"
    "Content-Type: text/html\r\n"
    "\r\n"
    "<html>"
    "<head><title>Sorry </title></head>\r\n"
    "<body><p>最近有点方了!</p></body>"
    "</html>";
    
    write(cfd, estr, strlen(estr));
}

inline void 
response_200(int cfd) {
    const char * estr = 
    "HTTP/1.0 200 OK\r\n"
    "Server: wz simple httpd 1.0\r\n"
    "Content-Type: text/html\r\n"
    "\r\n";
    
    write(cfd, estr, strlen(estr));
}

void 
response_file(int cfd, const char * path) {
    char buf[BUFSIZ];
    FILE * txt = fopen(path, "r");
    
    // 如果文件解析错误, 给它个404
    if(NULL == txt) 
        response_404(cfd);
    else{
        //发送给200的报文头过去, 并发送文件内容过去
        response_200(cfd);
        while(!feof(txt) && fgets(buf, sizeof buf, txt))
            write(cfd, buf, strlen(buf));
        fclose(txt);
    }
}

int 
request_start(uint16_t * pport) {
    int sfd;
    struct sockaddr_in saddr = { AF_INET };
    
    CERR_IF(sfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP));
    // 监测一下是否要更换端口, 并绑定一下端口信息
    saddr.sin_port = pport && *pport ? htons(*pport) : 0;//判断存储端口的地址是否为空，且端口号是否为0
    CERR_IF(bind(sfd, (struct sockaddr *)&saddr, sizeof saddr));

    if(pport && !*pport) {
        socklen_t clen = sizeof saddr;
        CERR_IF(getsockname(sfd, (struct sockaddr*)&saddr, &clen));
        *pport = ntohs(saddr.sin_port);
    }

    // 开启监听任务
    CERR_IF(listen(sfd, SOMAXCONN));

    return sfd;
}

void * 
request_accept(void * arg) {
    char buf[BUFSIZ], path[BUFSIZ >> 1], type[BUFSIZ >> 2];
    char * lt, * rt, * query = NULL, * nb = buf;
    int iscgi, cfd = (int)arg;
    struct stat st;

    // 请求错误, 直接返回结果
    if(getfdline(cfd, buf, sizeof buf) <= 0) {
        response_501(cfd);
        close(cfd);
        return NULL;
    }
    printf("recv_buf = %s\n", buf);
    // 合法请求处理
    for(lt = type, rt = nb; !isspace(*rt) && (lt - type) < sizeof type - 1; *lt++ = *rt++)
        ;
    *lt = '\0';

    //同样处理合法与否判断, 出错了直接返回错误结果
    if((iscgi = strcasecmp(type, "POST")) && strcasecmp(type, "GET")) {
        response_501(cfd);
        close(cfd);
        return NULL;
    }

    // 在buf中 去掉空字符
    while(*rt && isspace(*rt))
        ++rt;

    // 这里得到路径信息, query url路径拼接
    *path = '.';
    for(lt = path + 1; (lt - path) < sizeof path - 1 && !isspace(*rt); *lt++ = *rt++)
        ;
    *lt = '\0';
    
    // 单独处理 get 获取 ? 后面数据, 不是 POST那就是 GET
    if(iscgi != 0) {
        for(query = path; *query && *query != '?'; ++query)
            ;
        if(*query == '?'){
            iscgi = 0;
            *query++ = '\0';
        }
    }
    
    // type , path 和 query 已经构建好了
    if(stat(path, &st) < 0) {
        response_404(cfd);
        close(cfd);
        return NULL;
    }
    printf("type = %s, path = %s, query = %s \n", type, path, query);
    // 合法情况, 执行, 写入, 读取权限. 监测是否是 CGI程序
    if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))
        iscgi = 0;
    if(!iscgi){
         printf("###Not CGI\n");
         response_file(cfd, path);                
    }
    else{
        printf("###Is CGI\n");
        request_cgi(cfd, path, type, query);
    }
    
    close(cfd);
    return NULL;
}

void 
request_cgi(int cfd, const char * path, const char * type, const char *  query) {
    pid_t pid;
    char c, buf[BUFSIZ];
    int pocgi[2], picgi[2];
    int i, contlen = -1; // 报文长度
    
    if(strcasecmp(type, "POST") == 0){
        while(getfdline(cfd, buf, sizeof buf) > 0 && strcmp("\n", buf)){
            buf[15] = '\0';
            if(!strcasecmp(buf, "Content-Length:"))
                contlen = atoi(buf + 16);
        }
        if(contlen == -1) { //错误的报文,直接返回错误结果
            response_400(cfd);
            return;
        }
    } 
    else { 
        // 读取报文头,就是过滤, 后面就假定是 GET
        while(getfdline(cfd, buf, sizeof buf) > 0 && strcmp("\n", buf))
            ;
    }
    
    //这里处理请求内容, 先处理错误信息
    if(pipe(pocgi) < 0) {
        response_500(cfd);
        return;
    }
    // 管道 是 0读取, 1写入
    if(pipe(picgi) < 0) {
        close(pocgi[0]), close(pocgi[1]);
        response_500(cfd);
        return;
    }
    if((pid = fork()) < 0){
        close(pocgi[0]), close(pocgi[1]);
        close(picgi[0]), close(picgi[1]);
        response_500(cfd);
        return;
    }

    // 这里就是多进程处理了, 先处理子进程
    if(pid == 0) {
        // dup2 让前者共享后者同样的文件表
        dup2(pocgi[1], STDOUT_FILENO); // 标准输出算作 pocgi管道的写入端
        dup2(picgi[0], STDIN_FILENO); // 标准输入做为 picgi管道的读取端
        close(pocgi[0]);
        close(picgi[1]);
        
        // 添加环境变量, 用于当前会话中
        sprintf(buf, "REQUEST_METHOD=%s", type);
        putenv(buf);
        // 继续凑环境变量串,放到当前会话种
        if(strcasecmp(buf, "POST") == 0)
            sprintf(buf, "CONTENT_LENGTH=%d", contlen);
        else
            sprintf(buf, "QUERY_STRING=%s", query);
        putenv(buf);
        // 成功的话调到 新的执行体上
        execl(path, path, NULL);
        
        // 这行代码原本是不用的, 但是防止 execl执行失败, 子进程没有退出.妙招
        exit(EXIT_SUCCESS);
    }
    // 父进程, 随便搞了, 先发送个OK
    write(cfd, "HTTP/1.0 200 OK\r\n", 17);
    close(pocgi[1]);
    close(picgi[0]);
    
    if(strcasecmp(type, "POST") == 0){
        // 将数据都写入到 picgi 管道中, 让子进程在 picgi[0]中读取 => STDIN_FILENO
        for(i = 0; i < contlen; ++i){
            read(cfd, &c, 1);
            write(picgi[1], &c, 1);
        }
    }
    //从子进程中 读取数据 发送给客户端, 多线程跨进程阻塞模型
    while(read(pocgi[0], &c, 1) > 0)
        write(cfd, &c, 1);
    
    close(pocgi[0]);
    close(picgi[1]);
    //等待子进程结束
    waitpid(pid, NULL, 0);
}