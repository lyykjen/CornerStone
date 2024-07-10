#include "glog/logging.h"   // glog 头文件

int main(int argc, char* argv[])
{
    google::InitGoogleLogging(argv[0]);    //初始化log的名字为daqing
    google::SetLogDestination(google::GLOG_INFO, "./log/prefix_");    //设置输出日志的文件夹和前缀，文件夹必须已经存在
                                                                    //第一个参数为日志级别，第二个参数表示输出目录及日志文件名前缀
    google::SetStderrLogging(google::GLOG_WARNING);//大于指定级别的日志都输出到标准输出
    google::SetLogFilenameExtension(".log");//在日志文件名中级别后添加一个扩展名。适用于所有严重级别
    FLAGS_colorlogtostderr = true;  // Set log color
    FLAGS_logbufsecs = 0;  // Set log output speed(s)
    FLAGS_max_log_size = 1024;  // Set max log file size
    FLAGS_stop_logging_if_full_disk = true;  // If disk is full

    LOG(INFO) << "hello i am info!";
    LOG(WARNING) << "hello i am warning test";  //输出一个Warning日志
    LOG(ERROR) << "hello i am error test";  //输出一个Error日志
    google::ShutdownGoogleLogging();

    return 0;
}
