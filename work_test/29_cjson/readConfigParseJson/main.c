#include<stdio.h>
#include<stdlib.h>
#include"cJSON.h"
#include<string.h>

typedef struct
{
    char firstName[32];
    char lastName[32];
    char email[64];
    int age;
    float height;
} PERSON;

int main(void)
{

    const char *fileName = "./config";
    FILE *fp = fopen(fileName, "rb");
    if(NULL == fp)
    {
        printf("fopen file failed\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    printf("file size: %d\n", file_size);
    fseek(fp, 0, SEEK_SET);

    char file_buf[2048] = {};
    int real_read = fread(file_buf, 1, file_size, fp);
    if (real_read != file_size)
    {
        printf("could not read file, giving up.\n");
        return -1;
    }
    printf("file content:\n%s\n", file_buf);

    //从缓冲区中解析出JSON结构
    cJSON * json= cJSON_Parse(file_buf);
    cJSON * c = json->child;
    PERSON person = {};

    while (c)
    {
        printf("stringKey:%s\n", c->string);
        cJSON *object=cJSON_GetObjectItem(json,c->string); 

        cJSON* item = cJSON_GetObjectItem(object,"firstName");
        memcpy(person.firstName,item->valuestring,strlen(item->valuestring));

        item = cJSON_GetObjectItem(object,"lastName");
        memcpy(person.lastName,item->valuestring,strlen(item->valuestring));

        item = cJSON_GetObjectItem(object,"email");
        memcpy(person.email,item->valuestring,strlen(item->valuestring));

        item = cJSON_GetObjectItem(object,"age");
        person.age = item->valueint;

        item = cJSON_GetObjectItem(object,"height");
        person.height = item->valuedouble;

        printf("firstName:%s\nlastName:%s\nemail:%s\nage:%d\nheight:%.02f\n\n",
                person.firstName,person.lastName,person.email,person.age,person.height);

        c = c->next;
    }

    
    cJSON_Delete(json);
    
    return 0;
}
