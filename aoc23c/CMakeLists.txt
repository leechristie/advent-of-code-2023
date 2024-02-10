cmake_minimum_required(VERSION 3.26)
project(aoc23c C)

set(CMAKE_C_STANDARD 17)

add_executable(aoc23c main.c
        day01.c
        days.h
        puzzletools.c
        puzzletools.h
        day04.c
        day02.c
        stringtools.c
        stringtools.h
        arraytools.c
        arraytools.h
        errortools.c
        errortools.h
        filetools.c
        filetools.h
        day08.c
        list.c
        list.h
        day09.c)
