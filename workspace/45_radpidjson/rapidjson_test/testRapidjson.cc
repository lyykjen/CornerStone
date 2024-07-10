// Taken from https://www.cnblogs.com/fnlingnzb-learner/p/10334988.html
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
 
using namespace rapidjson;
using namespace std;

int main() {

    //使用字符串缓冲器生成json
    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
 
    writer.StartObject();
 
    //1. 整数类型
    writer.Key("Int");
    writer.Int(1);
 
    //2. 浮点类型
    writer.Key("Double");
    writer.Double(12.0000001);
 
    //3. 字符串类型
    writer.Key("String");
    writer.String("This is a string");

    //4. 结构体类型
    writer.Key("Object");
    writer.StartObject();
    writer.Key("name");
    writer.String("qq849635649");
    writer.Key("age");
    writer.Int(25);
    writer.EndObject();

    writer.EndObject();

    string data = strBuf.GetString();
    cout << data << endl;


    //创建解析对象
    rapidjson::Document doc;
    //首先进行解析，没有解析错误才能进行具体字段的解析
    if(!doc.Parse(data.data()).HasParseError())
    {
        //1. 解析整数
        if(doc.HasMember("Int") && doc["Int"].IsInt())
        {
            cout << "Int = " << doc["Int"].GetInt() << endl;
        }
        //2. 解析浮点型
        if(doc.HasMember("Double") && doc["Double"].IsDouble())
        {
            cout << "Double = " << doc["Double"].GetDouble() << endl;
        }

        //3. 解析字符串
        if(doc.HasMember("String") && doc["String"].IsString())
        {
            cout << "String = " << doc["String"].GetString() << endl;
        }

        //4. 解析结构体
        if(doc.HasMember("Object") && doc["Object"].IsObject())
        {
            const rapidjson::Value& object = doc["Object"];
            if(object.HasMember("name") && object["name"].IsString())
            {
                cout << "Object.name = " << object["name"].GetString() << endl;
            }
            if(object.HasMember("age") && object["age"].IsInt())
            {
                cout << "Object.age = " << object["age"].GetInt() << endl;
            }
        }
    }

    return 0;
}