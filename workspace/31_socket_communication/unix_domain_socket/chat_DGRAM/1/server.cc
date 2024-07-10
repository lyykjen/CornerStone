// us_xfr.h
#include <string.h>
#include <zconf.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define BUF_SIZE 10             /* Maximum size of messages exchanged
                                   between client and server */

#define SV_SOCK_PATH "unix.socket"

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr, claddr;
    int sfd, j;
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
        numBytes = recvfrom(sfd, buf, BUF_SIZE, 0,
                            (struct sockaddr *) &claddr, &len);
        if (numBytes == -1) {
        	printf("recvfrom");
        	exit(EXIT_FAILURE);
    	}

        printf("Server received %ld bytes from %s\n", (long) numBytes,
                claddr.sun_path);
        /*FIXME: above: should use %zd here, and remove (long) cast */

        for (j = 0; j < numBytes; j++)
            buf[j] = toupper((unsigned char) buf[j]);

        if (sendto(sfd, buf, numBytes, 0, (struct sockaddr *) &claddr, len) !=
                numBytes)
           {
				 printf("sendto");
				 exit(EXIT_FAILURE);
			}
    }
}
