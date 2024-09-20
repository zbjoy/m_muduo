#!/bin/bash

set -e

# 如果没有 build 目录, 创建 build 目录
if [ ! -d `pwd`/build ]; then
    mkdir `pwd`/build
fi

rm -rf `pwd`/build/*

cd `pwd`/build &&
    cmake ../ &&
    make

# 回到项目根目录
cd ..

# 把 头文件 拷贝到 /usr/include//mymuduo,  so 库 拷贝到 /usr/lib   PATH
if [ ! -d /usr/include/mymuduo ]; then
    mkdir /usr/include/mymuduo
fi

for header in `ls *.h`
do
    cp $header /usr/include/mymuduo
done

cp `pwd`/lib/libmy_muduo.so /usr/lib

ldconfig
