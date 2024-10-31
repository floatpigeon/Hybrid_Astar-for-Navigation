cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_STANDARD 11=7)

include_directories(include)

add_executable(Project src/main.cpp src/map.cpp src/hybrid_Astar.cpp)