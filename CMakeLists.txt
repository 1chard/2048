cmake_minimum_required(VERSION 3.5)

project(2048 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -lncurses)

add_executable(2048 2048.cpp main.cpp)
