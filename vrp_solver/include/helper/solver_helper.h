//
// Created by petkovic on 01.04.25.
//

#ifndef SOLVER_HELPER_H
#define SOLVER_HELPER_H

#include <models/vehicle.h>
#include <models/graph.h>
#include <solver/solver.h>
#include <solver/nearest_neighbor.h>
#include <helper/command_line_parser.h>
#include <solver/savings_clark_wright.h>
#include <memory>    // using smart pointers

class SolverHelper {
public:
    static std::unique_ptr<Solver> createSolver(Graph &graph, Vehicle &vehicle, const AlgorithmType algorithmType);
};


#endif //SOLVER_HELPER_H
