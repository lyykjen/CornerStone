#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "document.h"

using namespace std;

std::vector<std::string> g_SysKey= {
"BILLDAYFLAG",
"BILLINGTYPE",
"BLACKLIST_AUTHFAIL_NUM",
"BLACKLIST_LOCK_CYCLE",
"BLACKLIST_STAT_CYCLE",
"BUDGET",
"BUDGETFLOW",
"BUDGETTIME",
"CHECKCAMPUSID",
"CLOSEDAY",
"CUCAreaNo",
"DEADONLINECHECK",
"DELAYTIMETHRESHOLD",
"DOWNBANDWIDTH_WITHIPTVONLINE",
"FLOWOVERTHRESHOLD",
"FLOWSHORTTHRESHOLD",
"FLOWUNIT",
"MAXDOWNBANDWIDTH_DSL",
"MAXDOWNBANDWIDTH_LAN",
"MaxSessionFlowOverValue",
"MAXSESSIONTIMEOUT",
"MaxSessionTimeOverValue",
"MAXUPBANDWIDTH_DSL",
"MAXUPBANDWIDTH_LAN",
"OldBoxDomainList",
"POLICYCATCHFLAG",
"PppoeNoAuthFlag",
"PppoeNoAuthFlagDomainList",
"PppoeNoAuthFlagDownBandWidth",
"PppoeNoAuthFlagSessionTimeout",
"PppoeNoAuthFlagUpBandWidth",
"REALMNAME_SPECIALCHARACTER",
"RESERVEDCALLINGNO",
"SHORTFEEVENDOR",
"TIMEOVERTHRESHOLDD",
"TIMESHORTTHRESHOLD",
"TIMEUNIT",
"UPBANDWIDTH_WITHIPTVONLINE",
"USERNAME_PREFIX",
"USERNAME_SUFFIX",
"WIFIDynamicPwdSessionTimeout",
"WIFIIdleTimeout",
"WIFIPostpaidSessionTimeout",
"WIFIPrepaidSessionTimeout"
};

bool parseString()
{
	std::ifstream t("./BD_SYS_CONFIG.json");
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	rapidjson::Document doc;
    bool ret = doc.Parse(str.data()).HasParseError();
	if(!ret)
    {
		cout << "rapidjson Parse string Begin..." << endl;
		for(auto &key : g_SysKey)
		{
			if(doc.HasMember(key.data()) && doc[key.data()].IsString())
			{
				string value = doc[key.data()].GetString();
				cout << key<< " = "<<value  << endl;
			}
		}
		cout << "rapidjson Parse string End...\n" << endl;
	}
	else
	{
		cout << "rapidjson Parse string error" << endl;
		return false;
	}

    return true;
}

bool parseArray()
{
	std::ifstream t("./BD_SYS_CONFIG2.json");
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	rapidjson::Document doc;
    bool ret = doc.Parse(str.data()).HasParseError();
	if(!ret)
    {
		cout << "rapidjson Parse Array Begin..." << endl;
		for(auto &key : g_SysKey)
		{
			if(doc.HasMember(key.data()) && doc[key.data()].IsArray())
			{
				const rapidjson::Value& array = doc[key.data()];
				//size_t len = array.Size();
				if(array[0].IsString()){
					cout << key << " = " << array[0].GetString() << endl;
				}
				
			}
		}
		cout << "rapidjson Parse Array End...\n" << endl;
	}
	else
	{
		cout << "rapidjson Parse Array error" << endl;
		return false;
	}

    return true;
}

bool parseStruct()
{
	std::ifstream t("./BD_SYS_CONFIG3.json");
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	rapidjson::Document doc;
    bool ret = doc.Parse(str.data()).HasParseError();
	if(!ret)
	{
		cout << "rapidjson Parse struct Begin..." << endl;
		if(doc.HasMember("GLOBAL") && doc["GLOBAL"].IsArray())
		{
			const rapidjson::Value& array = doc["GLOBAL"];
			size_t len = array.Size();
			for(size_t i = 0; i < len; i++)
			{
				const rapidjson::Value& object = array[i];
				//为防止类型不匹配，一般会添加类型校验
				if(object.IsObject())
				{
					cout << "ObjectArray[" << i << "]: ";
					if(object.HasMember("name") && object["name"].IsString()){
						cout << "name=" << object["name"].GetString();
					}
					if(object.HasMember("value") && object["value"].IsString()){
						cout << ", value=" << object["value"].GetString();
					}
					if(object.HasMember("comment") && object["comment"].IsString()){
						cout << ", comment="  << object["comment"].GetString()<< endl;
					}
				}
			}
		}
		cout << "rapidjson Parse struct End...\n" << endl;
	}
	else
	{
		cout << "rapidjson Parse struct error" << endl;
		return false;
	}
	
	return true;
}

bool goThrough()
{
	std::ifstream t("./BD_SYS_CONFIG2.json");
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	rapidjson::Document doc;
    bool ret = doc.Parse(str.data()).HasParseError();
	if(!ret)
	{
		cout << "rapidjson go through Begin..." << endl;
		rapidjson::Value& js_value = doc;
		for(auto iter = js_value.MemberBegin(); iter != js_value.MemberEnd(); ++iter)
		{
			auto key = (iter->name).GetString();
			if(js_value[key].IsArray()){
				const rapidjson::Value& array = js_value[key];
				if(array[0].IsString()){
					cout << key << " = " << array[0].GetString() << endl;
				}
			}
		}
		cout << "rapidjson go through End...\n" << endl;
	}

	return true;
}

int main()
{
	if(!parseString())
		return -1;

	if(!parseArray())
		return -1;

	if(!goThrough())
		return -1;

	if(!parseStruct())
		return -1;
    return 0;
}