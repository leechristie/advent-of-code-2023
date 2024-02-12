cmake_minimum_required(VERSION 3.26)
project(aoc23cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc23cpp main.cpp
        days.hpp
        day01.cpp
        puzzle.cpp
        puzzle.hpp
        day02.cpp
        day09.cpp
)
