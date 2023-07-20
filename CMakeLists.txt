cmake_minimum_required(VERSION 3.16)
project(LTC2948-Control C)
add_executable(ChipControl LTC2943.c ChipControl.c main.c)
