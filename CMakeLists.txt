cmake_minimum_required(VERSION 3.17)
project(Assegnamento_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assegnamento_2
        Train.cpp Train.h
        TimeTable.cpp TimeTable.h
        High_speed_train_super.h High_speed_train_super.cpp
        High_speed_train.h High_speed_train.cpp
        Regional_train.h Regional_train.cpp
        Station.h Station.cpp
        StationLink.h
        TimeTable.h TimeTable.cpp
        Train_type.h Train_status.h
        main_station.cpp  )
