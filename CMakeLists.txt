cmake_minimum_required(VERSION 3.21)
project(Ringct_rework C)

set(CMAKE_C_STANDARD 23)

add_executable(Ringct_rework
        main.c
        params.h
        poly.c poly.h
        sha3.c sha3.h
        entropy.c entropy.h
        sampler.c sampler.h
        tables.c tables.h

        matrix.c matrix.h L2RS.c L2RS.h reduce.c reduce.h ntt.c ntt.h precomp.c)
