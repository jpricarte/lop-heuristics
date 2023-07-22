cmake_minimum_required(VERSION 3.2)
project(tabu)

set(CMAKE_CXX_STANDARD 17)

add_executable(tabu main.cpp Lop.cpp Lop.h Heuristics.cpp Heuristics.h Constructive.cpp Constructive.h)
