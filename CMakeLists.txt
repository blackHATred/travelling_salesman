cmake_minimum_required(VERSION 3.26)
project(AandSD)

set(CMAKE_CXX_STANDARD 17)

add_executable(AandSD main.cpp
        modules/edge.cpp
        modules/point.cpp
        modules/dsu.cpp
        modules/graph.cpp)
