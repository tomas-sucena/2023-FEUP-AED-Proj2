cmake_minimum_required(VERSION 3.24)
project(AirportAED)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(AirportAED
        src/Graph.cpp
        src/Graph.h
        src/main.cpp
        src/Reader.cpp
        src/Reader.h)
