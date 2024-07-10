#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
int main() {
    // 创建一个控制台日志记录器
    auto console_logger = spdlog::stdout_color_mt("console");
    // 设置日志记录级别为debug
    console_logger->set_level(spdlog::level::debug);
    // 记录不同级别的日志
    console_logger->trace("This is a trace message.");
    console_logger->debug("This is a debug message.");
    console_logger->info("This is an info message.");
    console_logger->warn("This is a warning message.");
    console_logger->error("This is an error message.");
    return 0;
}