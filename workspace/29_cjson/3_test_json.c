
#include<stdio.h>
#include<stdlib.h>
#include"cJSON.h"
#include<string.h>
/*
{

"people":[

{"firstName":"z","lastName":"Jason","email":"bbbb@126.com","height":1.67},

{"lastName":"jadena","email":"jadena@126.com","age":8,"height":1.17},

{"email":"cccc@126.com","firstName":"z","lastName":"Juliet","age":36,"height":1.55}

]

} 
*/

typedef struct  
{  
    int id;  
    char firstName[32];  
    char lastName[32];  
    char email[64];  
    int age;  
    float height;  
}people; 

int main(void)
{
	people worker[3]={{0}};  
    char *data = "{\"people\":[\
    {\"firstName\":\"z\",\"lastName\":\"Jason\",\"email\":\"bbbb@126.com\",\"height\":1.67},\
    {\"lastName\":\"jadena\",\"email\":\"jadena@126.com\",\"age\":8,\"height\":1.17},\
    {\"email\":\"cccc@126.com\",\"firstName\":\"z\",\"lastName\":\"Juliet\",\"age\":36,\"height\":1.55}\
    ]}";
    //从缓冲区中解析出JSON结构
    cJSON * json= cJSON_Parse(data);

    cJSON *arrayItem=cJSON_GetObjectItem(json,"people"); 

     if(arrayItem!=NULL)
     {
     	int size=cJSON_GetArraySize(arrayItem);//获取数组长度
     	printf("cJSON_GetArraySize: size=%d\n",size);  

     	for(int i=0;i<size;i++)  
        {  
            printf("i=%d\n",i);  
            cJSON *object=cJSON_GetArrayItem(arrayItem,i);//获取数组成员

           cJSON *item=cJSON_GetObjectItem(object,"firstName");  
            if(item!=NULL)  
            {  
                printf("cJSON_GetObjectItem: type=%d, string is %s\n",item->type,item->string);  
                memcpy(worker[i].firstName,item->valuestring,strlen(item->valuestring));  
            }  

            item=cJSON_GetObjectItem(object,"lastName");  
            if(item!=NULL)  
            {  
                printf("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s\n",item->type,item->string,item->valuestring);  
                memcpy(worker[i].lastName,item->valuestring,strlen(item->valuestring));  
            }  

            item=cJSON_GetObjectItem(object,"email");  
            if(item!=NULL)  
            {  
                printf("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s\n",item->type,item->string,item->valuestring);  
                memcpy(worker[i].email,item->valuestring,strlen(item->valuestring));  
            }  

            item=cJSON_GetObjectItem(object,"age");  
            if(item!=NULL)  
            {  
                printf("cJSON_GetObjectItem: type=%d, string is %s, valueint=%d\n",item->type,item->string,item->valueint);  
                worker[i].age=item->valueint;  
            }  
            else  
            {  
                printf("cJSON_GetObjectItem: get age failed\n");  
            }  

            item=cJSON_GetObjectItem(object,"height");  
            if(item!=NULL)  
            {  
                printf("cJSON_GetObjectItem: type=%d, string is %s, value=%f\n",item->type,item->string,item->valuedouble);  
                worker[i].height=item->valuedouble;  
            }  
        }  
     }  

     for(int i=0;i<3;i++)
     {
     	printf("i=%d, firstName=%s,lastName=%s,email=%s,age=%d,height=%f\n",  
                i,  
                worker[i].firstName,  
                worker[i].lastName,  
                worker[i].email,  
                worker[i].age,  
                worker[i].height);  
     }

    cJSON_Delete(json);
    
    return 0;
}
