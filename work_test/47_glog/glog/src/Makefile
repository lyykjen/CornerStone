all:
	g++ -std=c++11 glogtest.cc  -o glogtest -I../glog-0.5.0/src -I../glog-0.5.0/build -I../gflags-2.2.0/build/include -L../glog-0.5.0/build -L../gflags-2.2.0/build/lib  -lglog -lgflags
	g++ -std=c++11 glogtest2.cc  -o glogtest2 -I../glog-0.5.0/src -I../glog-0.5.0/build -I../gflags-2.2.0/build/include -L../glog-0.5.0/build -L../gflags-2.2.0/build/lib  -lglog -lgflags
clean: 
	rm -rf glogtest glogtest2
