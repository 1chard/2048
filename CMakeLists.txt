cmake_minimum_required(VERSION 3.5)

project(2048curses LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -lncurses)

add_subdirectory(lib2048)

add_executable(2048curses window.cpp main.cpp)
target_link_libraries(2048curses PUBLIC 2048)
