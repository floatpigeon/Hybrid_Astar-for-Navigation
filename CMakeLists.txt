cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Project src/main.cpp)
# add_executable(Project src/test.cpp src/map.cpp src/hybrid_Astar.cpp src/map_creator.cpp)
