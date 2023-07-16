cmake_minimum_required(VERSION 3.26)
project(lop)

set(CMAKE_CXX_STANDARD 20)

add_executable(lop main.cpp Lop.cpp Lop.h Heuristics.cpp Heuristics.h)
