#include<stdio.h>
#include<stdlib.h>
#include"cJSON.h"
#include<string.h>
#include<stdint.h>

typedef struct
{
    char firstName[32];
    char lastName[32];
    char email[64];
    int age;
    float height;
} PERSON;

int32_t parseJson(cJSON *json, uint8_t index)
{
    if(NULL == json)
    {
        //printf("[Error]: json%u is NULL\n", index);
        return -1;
    }

    while (json)
    {
        printf("\n********** %u **********\n",index);
        printf("Key: %s, ", json->string);
        printf("Value: %s\n",cJSON_Print(json));

        parseJson(json->child,index+1);

        json = json->next;
    }
    return 0;
}

int main(void)
{

    const char *fileName = "./sipConfig";
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
    //printf("file content:\n%s\n", file_buf);

    //从缓冲区中解析出JSON结构
    cJSON *json= cJSON_Parse(file_buf);
    cJSON *c1 = json->child;
    parseJson(c1,1);

    /*cJSON *c2 = c1->child;
    parseJson(c2,2);

    cJSON *c3 = c2->child;
    parseJson(c3,3);

    cJSON *c4 = c3->child;
    parseJson(c4,4);*/


#if 0
    while (c)
    {
        printf("stringKey:%s\n", c->string);
        cJSON *object=cJSON_GetObjectItem(json,c->string); 
        printf("data1:%s\n",cJSON_Print(object));

        cJSON * c1 = c->child;
        if(NULL == c1)
        {
            printf("json->child->child is null\n");
        }
        else
        {
            while(c1)
            {
                printf("stringKey:%s\n", c1->string);
                printf("data2:%s\n",cJSON_Print(c1));
                //cJSON *object=cJSON_GetObjectItem(c,c1->string); 
                //printf("data2:%s\n",cJSON_Print(object));
                c1 = c1->next;
            }
            
        }



#if 0
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
#endif
        c = c->next;
    }
#endif
    
    cJSON_Delete(json);
    
    return 0;
}
