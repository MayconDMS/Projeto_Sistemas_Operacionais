cmake_minimum_required(VERSION 4.2)
project(Projeto_Sistemas_Operacionais C)

set(CMAKE_C_STANDARD 11)

add_executable(Projeto_Sistemas_Operacionais pcb.c
        cmake-build-debug/pcb.h
        main.c)
