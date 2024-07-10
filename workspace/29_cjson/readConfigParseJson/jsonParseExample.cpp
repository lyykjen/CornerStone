#include <iostream>
#include <stdio.h>
#include "cJSON.h"
#include <string>
#include <map>
using namespace std;

map<string,string> MapAnalysisJSON(string ResMessage)
{
	map<string,string> mapResMessage;
 
	cJSON* cjson = cJSON_Parse(ResMessage.c_str()); 
 
	if(cjson == NULL)
	{
		printf("json pack into cjson error...");
	}
	else
	{
		cJSON_Print(cjson);              
	}
 
	cJSON * c = cjson->child;
	while (c)
	{
		mapResMessage.insert(pair<string,string>(c->string,c->valuestring));
		c = c->next;
	}
	c = NULL;
 
	return mapResMessage;
 
}
 
 
int main()
{
	string json_string = "{\"ResCode\":\"000\",\"ResDesc\":\"业务受理成功\",\"ServiceResMsg\":\"这是XML格式字串\"}";
	map<string,string> recmap;
 
 
    recmap = MapAnalysisJSON(json_string);
 
	if (recmap.size() == 0)
	{
		cout << "recmap is empty!";
	}
 
	for (map<string,string>::iterator iter = recmap.begin();iter != recmap.end();iter++)
	{
		cout << iter->first << " " << iter->second << endl;
	}
 
 
 
	return 0;
}