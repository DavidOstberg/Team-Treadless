cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#file(GLOB libsocketCAN_src "src/*.cpp")
file(GLOB libsocketCAN_src "src/socketcan_cpp.cpp")

project(socketCAN VERSION 1.0)

add_library(socketCanlib STATIC src/socketcan_cpp.cpp)
target_include_directories(socketCanlib PUBLIC include)





