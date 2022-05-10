cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main VERSION 1.0)

add_subdirectory(InputHandler)
add_subdirectory(Emulator)

# file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/InputHandler/CMakeLists.txt" LOC_PATH)
# file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/Emulator/CMakeLists.txt" LOC_PATH)


add_compile_options(-Wall -Wextra -Wpedantic)


