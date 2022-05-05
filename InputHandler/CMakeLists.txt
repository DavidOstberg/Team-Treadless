cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(inputHandler VERSION 1.0)

add_executable(inputHandler
            main.cpp
            src/ncurse_input.cpp
)

target_include_directories(
    inputHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries(inputHandler PUBLIC socketCanlib)


find_package(Curses REQUIRED )
target_include_directories(inputHandler PUBLIC ${CURSES_INCLUDE_DIRS})

target_link_libraries(inputHandler PUBLIC ${CURSES_LIBRARIES})
