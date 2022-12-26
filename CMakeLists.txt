cmake_minimum_required(VERSION 3.24)
project(AirportAED)

set(CMAKE_CXX_STANDARD 14)

add_executable(AirportAED
        src/main.cpp src/Reader.cpp src/Reader.h)
