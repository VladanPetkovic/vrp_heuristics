cmake_minimum_required(VERSION 3.20)
project(vrp_solver)

set(CMAKE_CXX_STANDARD 23)

add_executable(vrp_solver
        src/main.cpp
        src/graph.cpp
        src/graph_builder.cpp
)
