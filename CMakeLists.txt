cmake_minimum_required(VERSION 3.12)
project(Labo04)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wconversion -Wextra -pedantic")

add_executable(Labo04
        main.cpp)
