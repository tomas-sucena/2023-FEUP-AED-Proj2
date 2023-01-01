cmake_minimum_required(VERSION 3.16.3)
project(AirportAED)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(AirportAED
        src/AirGraph.cpp
        src/AirGraph.h
        src/Helpy.cpp
        src/Helpy.h
        src/data/Airline.cpp
        src/data/Airline.h
        src/data/Airport.cpp
        src/data/Airport.h
        src/Helpy.cpp
        src/Helpy.h
        src/main.cpp
        src/Reader.cpp
        src/Reader.h)
