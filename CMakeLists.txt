cmake_minimum_required(VERSION 3.24)
project(AEDproject)

set(CMAKE_CXX_STANDARD 17)

add_executable(AEDproject src/main.cpp schedule src/User.h src/User.cpp src/Authentication.h src/Authentication.cpp src/Lesson.h src/Lesson.cpp src/UcClass.cpp src/UcClass.h src/Schedule.h src/Schedule.cpp)
