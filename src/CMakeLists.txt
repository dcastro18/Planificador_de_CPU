cmake_minimum_required(VERSION 3.21)
project(src C)

set(CMAKE_C_STANDARD 11)

include_directories(Client)
include_directories(Loader)

add_executable(src
        Client/AUtomatic.c
        Client/Automatic.h
        Client/Manual.c
        Client/Manual.h
        Loader/Loader.c
        Loader/Loader.h
        main.c)
