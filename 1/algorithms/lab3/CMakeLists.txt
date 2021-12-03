cmake_minimum_required(VERSION 3.14)  # CMake version check
project(lab3)                         # Create project "lab3"
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

add_executable(lab3 main.cpp)
add_subdirectory(test)