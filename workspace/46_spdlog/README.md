spdlog新版本提供了静态库方式,这样比原来的header only方式显著提升了编译速度。

源码编译spdlog:

```shell
tar zxf spdlog-1.8.2.tar.gz
cd spdlog-1.8.2 && mkdir build && cd build
cmake .. && make -j
```

编译生成静态库:spdlog-1.8.2/build/libspdlog.a