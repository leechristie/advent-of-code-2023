cmake_minimum_required(VERSION 3.26)
project(aoc23c C)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${COMMON_FLAGS} -g3 -O0 -fsanitize=address,undefined -fno-omit-frame-pointer -fstack-protector-strong -fno-inline -fno-eliminate-unused-debug-types -fdiagnostics-color=always -fno-common")

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
        old_mathtools.h
        file_tools.c
        file_tools.h
        error_tools.c
        error_tools.h
        string_tools.c
        string_tools.h)
