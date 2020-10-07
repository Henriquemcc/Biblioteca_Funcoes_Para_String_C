cmake_minimum_required(VERSION 3.17)
project(Biblioteca_Funcoes_Para_String_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Biblioteca_Funcoes_Para_String_C
        funcoesParaStrings.h
        test.c)
