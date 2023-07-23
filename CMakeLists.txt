cmake_minimum_required(VERSION 3.2)
project(greedy)

set(CMAKE_CXX_STANDARD 17)

add_executable(greedy main.cpp Lop.cpp Lop.h Heuristics.cpp Heuristics.h Constructive.cpp Constructive.h)
