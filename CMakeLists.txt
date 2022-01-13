cmake_minimum_required(VERSION 3.21)
project(Ringct_rework C)

set(CMAKE_C_STANDARD 23)

add_executable(Ringct_rework main.c poly.c poly.h)
