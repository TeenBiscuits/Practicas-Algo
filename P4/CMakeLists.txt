cmake_minimum_required(VERSION 3.22)
project(P4 C)

set(CMAKE_C_STANDARD 99)

add_executable(P4 main.c
        monticulos.c
        monticulos.h)

target_link_libraries(P4 m)
