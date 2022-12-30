cmake_minimum_required(VERSION 3.24)
project(AirportAED)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(AirportAED
        src/data/Airline.cpp
        src/data/Airline.h
        src/data/Airport.cpp
        src/data/Airport.h
        src/main.cpp
        src/Reader.cpp
        src/Reader.h src/AirGraph.cpp src/AirGraph.h)
