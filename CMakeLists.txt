cmake_minimum_required(VERSION 3.16.3)
project(AirportAED)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(AirportAED
        src/AirGraph.cpp
        src/AirGraph.h
        src/Airline.cpp
        src/Airline.h
        src/Airport.cpp
        src/Airport.h
        src/Helpy.cpp
        src/Helpy.h
        src/libfort/fort.c
        src/libfort/fort.h
        src/main.cpp
        src/Reader.cpp
        src/Reader.h)
