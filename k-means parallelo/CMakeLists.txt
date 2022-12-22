cmake_minimum_required(VERSION 3.23)
project(k_means_parallelo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp ")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(k_means_parallelo main.cpp Point.h Cluster.h)
