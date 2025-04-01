cmake_minimum_required(VERSION 3.20)
project(vrp_solver)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(vrp_solver
        # main
        src/main.cpp
        # solver
        src/solver/solver.cpp
        src/solver/nearest_neighbor.cpp
        # models
        src/models/graph.cpp
        src/models/node.cpp
        src/models/route.cpp
        src/models/vehicle.cpp
        # helper
        src/helper/command_line_parser.cpp
        src/helper/solver_helper.cpp
        src/helper/xml_converter.cpp
        # lib
        src/lib/pugixml.cpp
)
