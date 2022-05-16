cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Emulator VERSION 1.0)

add_executable(emulator
            main.cpp
            src/emulator.cpp
            src/CAN_reader.cpp
            src/decoding.cpp
)


target_link_libraries(emulator PUBLIC socketCanlib
                                        pthread)
target_include_directories(emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


