cmake_minimum_required(VERSION 3.22)
project(Implementaciones C)

set(CMAKE_C_STANDARD 99)

add_executable(Implementaciones main.c
        pilas.c
        pilas.h
        colas.c
        colas.h
        listas.c
        listas.h)
