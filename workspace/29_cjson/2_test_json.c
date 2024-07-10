#include<stdio.h>
#include<stdlib.h>
#include"cJSON.h"
#include<string.h>
/*
{
         "person":
         {
                   "firstName":"z",

                   "lastName":"jadena",

                   "email":"jadena@126.com",

                   "age":8,

                   "height":1.17
         }       
}
*/

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
    char *data = "{\"person\":{\"firstName\":\"z\",\"lastName\":\"jadena\", \"email\":\"jadena@126.com\", \"age\":8,\"height\":1.17}}";
    //从缓冲区中解析出JSON结构
    cJSON * json= cJSON_Parse(data);

    cJSON *object=cJSON_GetObjectItem(json,"person"); 

    cJSON* item;

    PERSON person;

    item = cJSON_GetObjectItem(object,"firstName");

    memcpy(person.firstName,item->valuestring,strlen(item->valuestring));

    item = cJSON_GetObjectItem(object,"lastName");

    memcpy(person.lastName,item->valuestring,strlen(item->valuestring));

    item = cJSON_GetObjectItem(object,"email");

    memcpy(person.email,item->valuestring,strlen(item->valuestring));

    item = cJSON_GetObjectItem(object,"age");

    person.age = item->valueint;

    item = cJSON_GetObjectItem(object,"height");

    person.height = item->valuedouble;

    printf("firstName:%s\nlastName:%s\nemail:%s\nage:%d\nheight:%.02f\n",person.firstName,person.lastName,person.email,person.age,person.height);

    cJSON_Delete(json);
    
    return 0;
}
