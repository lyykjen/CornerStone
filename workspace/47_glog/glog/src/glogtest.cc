/* glogtest.cc */

#include <cstdio>
#include <glog/logging.h>

int main(int argc, char* argv[]) 
{
    // Initialize Google’s logging library.
    google::InitGoogleLogging(argv[0]);//初始化一个log

	FLAGS_alsologtostderr = 1;//输出到控制台

    std::printf("Hello google glog!\n");

    int num_cookies = 1234;
    LOG(INFO) << "Found " << num_cookies << " cookies";//输出一个Info日志
    std::printf("INFO!\n");

    LOG(WARNING) << "Found " << ++num_cookies << " cookies";//输出一个Warning日志
    std::printf("Warning!\n");

    LOG(ERROR) << "Found " << ++num_cookies << " cookies";//输出一个Error日志
    std::printf("Error!\n");

//    LOG(FATAL) << "Found " << ++num_cookies << " cookies";//输出一个Fatal日志，这是最严重的日志并且输出之后会中止程序,暂时注掉
    std::printf("FATAL!\n");

	google::ShutdownGoogleLogging();//不用log的时候应该释放掉，不然会内存溢出

    return 0;
}


