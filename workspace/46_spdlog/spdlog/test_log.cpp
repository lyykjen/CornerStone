#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
namespace spd = spdlog;
int main()
{
       //创建文件名类似于： daily_log_2020_05-28.txt，如果程序不退出的话，就是每天2:30 am创建新的文件
        auto console= spd::daily_logger_mt("upfile00", "./log/daily_log.txt", 2, 20);
        //写入log文件
        string s="success";
        console->info("test s ={}",s);//{}可以表示变量，跟printf的语法类似
        console->info("log is ok");//info表示是提示信息级别
        console->warn("warning");//warn表示警告信息级别
        console->error("this is a error");//error表示错误信息级别
        cout << "success" << endl;//控制台输出
        return 0;
}

