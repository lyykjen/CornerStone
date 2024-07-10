#include <unistd.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
int main()
{
        auto logger = spdlog::basic_logger_mt("basic_logger", "./log/basic.log");


        while(1)
        {
                logger->info("test s ={}","success");//{}可以表示变量，跟printf的语法类似
                logger->info("log is ok");//info表示是提示信息级别
                logger->warn("warning");//warn表示警告信息级别
                logger->error("this is a error");//error表示错误信息级别
                logger->flush();
                usleep(500000);
        }


        return 0;

}
