cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CAN_Reader VERSION 1.0)

add_library(socketCanlib STATIC src/socketcan_cpp.cpp)
target_include_directories(socketCanlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(vcanReader vcanReader.cpp)
target_link_libraries(vcanReader PUBLIC socketCanlib)
target_include_directories(vcanReader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
