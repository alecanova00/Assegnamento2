cmake_minimum_required(VERSION 3.17)
project(Assegnamento_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assegnamento_2
        Train.cpp
        Train.h TimeTable.cpp TimeTable.h  )
