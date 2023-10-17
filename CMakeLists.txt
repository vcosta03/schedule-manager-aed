cmake_minimum_required(VERSION 3.24)
project(AEDproject)

set(CMAKE_CXX_STANDARD 17)

add_executable(AEDproject main.cpp schedule User.h User.cpp Authentication.h Authentication.cpp)
