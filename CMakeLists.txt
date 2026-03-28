cmake_minimum_required(VERSION 3.13)
project(GrizzGame CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(GrizzGame main.cpp
        music.cpp)
target_link_libraries(GrizzGame ncurses tinfo)