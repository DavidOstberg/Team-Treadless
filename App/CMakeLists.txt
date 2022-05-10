cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main VERSION 1.0)

add_subdirectory(InputHandler)
add_subdirectory(Emulator)

add_compile_options(-Wall -Wextra -Wpedantic)


