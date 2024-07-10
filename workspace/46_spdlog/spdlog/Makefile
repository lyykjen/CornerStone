all:
	g++ -std=c++11 -I../spdlog-1.8.2/include test_log.cpp -o test_log
	g++ -std=c++11 -I../spdlog-1.8.2/include console.cc -o console
	g++ -std=c++11 -DSPDLOG_COMPILED_LIB -I../spdlog-1.8.2/include Basic_file_logger.cc -o Basic_file_logger -L../spdlog-1.8.2/build -lspdlog
