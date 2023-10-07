> glog和gflags有版本依赖关系,单独安装glog时会提示安装指定版本gflags,一般情况下，先安装gflags后安装glog。

## 安装gflags

```shell
tar zxf gflags-2.2.0.tar.gz
cd gflags-2.2.0
mkdir build && cd build
cmake ..  -DBUILD_SHARED_LIBS=ON -DGFLAGS_NAMESPACE=google -DCMAKE_CXX_FLAGS=-fPIC ..
make -j4 //编译生成动态库:gflags-2.2.0/build/lib/libgflags.so
#sudo make install //根据需要安装到合适的位置
```

## 安装glog

```shell
tar zxf glog-0.5.0.tar.gz
cd glog-0.5.0
#需要指定gflags安装位置
cmake -DGFLAGS_NAMESPACE=google -DCMAKE_CXX_FLAGS=-fPIC -DBUILD_SHARED_LIBS=ON -DCMAKE_PREFIX_PATH=~/software/gflags-2.2.0/build ..
make -j4 //编译生成动态库:glog-0.5.0/build/libglog.so
#sudo make install //根据需要安装到合适的位置
```

## 编译与运行

编译时需要指定头文件和动态库位置，如：

```shell
g++ -std=c++11 glogtest2.cc  -o glogtest2 -I../glog-0.5.0/src -I../glog-0.5.0/build -I../gflags-2.2.0/build/include -L../glog-0.5.0/build -L../gflags-2.2.0/build/lib  -lglog -lgflags
```

运行时需要在环境变量中加入动态库位置，如`glog/src/ld_library_path.sh`：

```shell
export LD_LIBRARY_PATH=~/software/glog/glog-0.5.0/build:~/software/glog/gflags-2.2.0/build/lib:$LD_LIBRARY_PATH 
```

