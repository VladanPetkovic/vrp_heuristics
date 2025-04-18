cmake_minimum_required(VERSION 3.20)
project(vrp_solver)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(vrp_solver
        # main
        src/main.cpp
        # solver
        src/solver/inter_route_improvement.cpp
        src/solver/lambda_opt.cpp
        src/solver/nearest_neighbor.cpp
        src/solver/nn_improvement.cpp
        src/solver/nn_lambda_opt.cpp
        src/solver/savings_clark_wright.cpp
        src/solver/savings_lambda_opt.cpp
        src/solver/savings_improvement.cpp
        src/solver/solver.cpp
        # models
        src/models/graph.cpp
        src/models/node.cpp
        src/models/route.cpp
        src/models/vehicle.cpp
        # helper
        src/helper/command_line_parser.cpp
        src/helper/performance_metrics.cpp
        src/helper/solver_helper.cpp
        src/helper/xml_converter.cpp
        # lib
        src/lib/pugixml.cpp
)
