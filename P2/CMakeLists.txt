cmake_minimum_required(VERSION 3.22)
project(P2 C)

set(CMAKE_C_STANDARD 99)

add_executable(P2 main.c
        ordenar.c
        ordenar.h)

target_link_libraries(P2 m)
