cmake_minimum_required(VERSION 3.20)
project(vrp_solver)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(vrp_solver
        # main
        src/main.cpp
        # app
        src/app/graph_builder.cpp
        # models
        src/models/graph.cpp
        src/models/node.cpp
        src/models/vehicle.cpp
        # helper
        src/helper/command_line_parser.cpp
        src/helper/time_helper.cpp
        # lib
        src/lib/pugixml.cpp
)
