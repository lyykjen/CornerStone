#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void file_type(const struct stat * get_message)
{
    mode_t mode = (*get_message).st_mode;
    if(S_ISREG(mode))
        printf("-");/*��ͨ�ļ�*/
    else if(S_ISDIR(mode))
        printf("d");/*Ŀ¼�ļ�*/
#if 1
    else if(S_ISCHR(mode))
        printf("c");/*�ַ��豸�ļ�*/
    else if(S_ISBLK(mode))
        printf("b");/*���豸�ļ�*/
    else if(S_ISFIFO(mode))
        printf("p");/*�ܵ��ļ�*/
    else if(S_ISLNK(mode))
        printf("l");/*�����ļ�*/
    else if(S_ISSOCK(mode))
        printf("s");/*socket�ļ�*/
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