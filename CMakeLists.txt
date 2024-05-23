cmake_minimum_required(VERSION 3.26)
project(lab7)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab7 main.cpp
        fio.h
        funcs.h
        funcs.cpp
        fio.cpp
        doctor.h
        doctor.cpp
        main.h)
