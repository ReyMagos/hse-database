cmake_minimum_required(VERSION 3.28)
project(hse_database C)

set(CMAKE_C_STANDARD 11)

add_executable(hse_database main.c utils.h database.h database.c actions.h actions.c
        utils.c)
