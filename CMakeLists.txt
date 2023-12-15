cmake_minimum_required(VERSION 3.27)
project(life_cpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(life_cpp main.cpp
        game.cpp
        game.h)
