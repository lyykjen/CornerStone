#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void file_type(const struct stat * get_message)
{
    mode_t mode = (*get_message).st_mode;
    if(S_ISREG(mode))
        printf("-");/*普通文件*/
    else if(S_ISDIR(mode))
        printf("d");/*目录文件*/
#if 1
    else if(S_ISCHR(mode))
        printf("c");/*字符设备文件*/
    else if(S_ISBLK(mode))
        printf("b");/*块设备文件*/
    else if(S_ISFIFO(mode))
        printf("p");/*管道文件*/
    else if(S_ISLNK(mode))
        printf("l");/*链接文件*/
    else if(S_ISSOCK(mode))
        printf("s");/*socket文件*/
	else 
		 printf("no file type can match!\n");
	 printf("\n");
#endif
}

int main() {
    struct stat buf;
    stat("/etc/hosts", &buf);
    printf("/etc/hosts file size = %d\n", (int)buf.st_size);
	file_type(&buf);
	/*
	if(S_ISDIR(buf.st_mode))
		printf("This is directory!\n");
	else
	{
		printf("This is not directory!\n");
		printf("This file's type is %d\n",buf.st_mode);
	}
	*/	
}