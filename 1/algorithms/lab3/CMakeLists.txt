cmake_minimum_required(VERSION 3.13)  # CMake version check
project(lab3)                         # Create project "lab3"
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES lab3.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(lab3 ${SOURCE_FILES})