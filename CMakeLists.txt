cmake_minimum_required(VERSION 3.24)
project(AEDproject)

set(CMAKE_CXX_STANDARD 17)

add_executable(AEDproject src/main.cpp src/User.h src/User.cpp src/Authentication.h src/Authentication.cpp src/Lesson.h src/Lesson.cpp src/UcClass.cpp src/UcClass.h src/Schedule.h src/Schedule.cpp src/Application.h src/Application.cpp src/Student.h src/Student.cpp src/Ticket.h src/Ticket.cpp)
