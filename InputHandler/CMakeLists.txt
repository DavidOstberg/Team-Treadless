cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(inputHandler VERSION 1.0)

add_library(socketCanlib STATIC src/socketcan_cpp.cpp)
target_include_directories(socketCanlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(inputHandler main.cpp)
target_link_libraries(inputHandler PUBLIC socketCanlib)


add_library(ncurseInputlib STATIC src/ncurse_input.cpp)
target_include_directories(ncurseInputlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(inputHandler PUBLIC ncurseInputlib)

find_package(Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS})

target_link_libraries(inputHandler PUBLIC ${CURSES_LIBRARIES})

add_executable(vcanReader src/vcanReader.cpp)
target_link_libraries(vcanReader PUBLIC socketCanlib)
