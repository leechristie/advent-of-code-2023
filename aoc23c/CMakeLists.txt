cmake_minimum_required(VERSION 3.26)
project(aoc23c C)

set(CMAKE_C_STANDARD 17)

add_executable(aoc23c main.c
        day01.c
        days.h
        old_puzzletools.c
        old_puzzletools.h
        day04.c
        day02.c
        old_stringtools.c
        old_stringtools.h
        old_arraytools.c
        old_arraytools.h
        old_errortools.c
        old_errortools.h
        old_filetools.c
        old_filetools.h
        day08.c
        old_list.c
        old_list.h
        day09.c
        day10.c
        old_matrix.c
        old_matrix.h
        day13.c
        old_mathtools.c
        old_mathtools.h)
