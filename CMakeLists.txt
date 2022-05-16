cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main VERSION 1.0)

add_subdirectory(lib/socketCAN)
add_subdirectory(App)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/App/InputHandler/CMakeLists.txt" LOC_PATH)
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/lib/socketCAN/CMakeLists.txt" LOC_PATH)
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/App/Emulator/CMakeLists.txt" LOC_PATH)
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/App/Avic/CMakeLists.txt" LOC_PATH)


add_compile_options(-Wall -Wextra -Wpedantic)


