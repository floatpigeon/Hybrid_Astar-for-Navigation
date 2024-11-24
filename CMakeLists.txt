cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(Project src/main.cpp src/Node.cpp src/GridMap.cpp src/HybridAstar.cpp src/EZUI.cpp src/map_identifier.cpp)
# add_executable(Project src/test.cpp)

# find_package(Eigen3 REQUIRED NO_MODULE)
# target_link_libraries(Project Eigen3::Eigen)

find_package(OpenCV REQUIRED)
target_link_libraries(Project ${OpenCV_LIBS} pthread)
include_directories(${OpenCV_INCLUDE_DIRS} ${Eigen3_INCLUDE_DIRS})

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")


# if run error please use:
# LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 ./Project
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
