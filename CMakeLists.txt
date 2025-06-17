cmake_minimum_required(VERSION 3.27)
project(HW6MAMAT)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW6MAMAT main.cpp
        packets.cpp
        L4.cpp
        L3.cpp)
