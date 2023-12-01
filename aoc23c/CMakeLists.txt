cmake_minimum_required(VERSION 3.26)
project(aoc23c C)

set(CMAKE_C_STANDARD 17)

add_executable(aoc23c main.c
        day01.c
        day01.h
        puzzle.c
        puzzle.h)
