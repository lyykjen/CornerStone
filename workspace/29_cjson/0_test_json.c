#include<stdio.h>
#include<stdlib.h>
#include"cJSON.h"

int main(void)
{
    char *data = "{\"love\":[\"LOL\",\"Go shopping\"]}";
    //从缓冲区中解析出JSON结构
    cJSON * json= cJSON_Parse(data);
    
    //将传入的JSON结构转化为字符串 并打印
    char *json_data = NULL;
    printf("data:%s\n",json_data = cJSON_Print(json));
    
    free(json_data);
    //将JSON结构所占用的数据空间释放
    cJSON_Delete(json);
    return 0;
}
