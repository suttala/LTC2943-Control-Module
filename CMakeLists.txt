cmake_minimum_required(VERSION 3.16)
project(LTC2948-Control C)
set (CMAKE_C_FLAGS "-Wall -Werror -pedantic")
add_executable(ChipControl LTC2943.c ChipControl.c main.c)
