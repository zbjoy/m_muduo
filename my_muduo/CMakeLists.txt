cmake_minimum_required(VERSION 2.5)

project(my_muduo)

#   my_muduo 最终编译成 so 动态库, 设置的动态库的路径
#   set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#   设置调试信息 并启动 CXX11 标准编译
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -fPIC")

#   定义参与编译的源代码文件
aux_source_directory(. SRC_LIST)

#   编译生成动态库 my_muduo
add_library(my_muduo SHARED ${SRC_LIST})


