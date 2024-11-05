cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_STANDARD 17)

set(Eigen3_DIR "/usr/include/eigen3")

find_package(Eigen3 REQUIRED NO_MODULE)

include_directories(include)

add_executable(Project src/main.cpp src/Node.cpp src/GridMap.cpp src/Hybrid_Astar.cpp)

target_link_libraries(Project Eigen3::Eigen)
