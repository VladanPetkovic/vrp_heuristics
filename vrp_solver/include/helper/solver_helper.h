//
// Created by petkovic on 01.04.25.
//

#ifndef SOLVER_HELPER_H
#define SOLVER_HELPER_H

#include <models/vehicle.h>
#include <models/graph.h>
#include <solver/solver.h>
#include <solver/iterated_local_search.h>
#include <solver/nn_lambda_opt.h>
#include <solver/nn_improvement.h>
#include <solver/savings_lambda_opt.h>
#include <solver/savings_improvement.h>
#include <solver/nearest_neighbor.h>
#include <solver/savings_clark_wright.h>
#include <helper/command_line_parser.h>
#include <memory>    // using smart pointers

class SolverHelper {
public:
    static std::unique_ptr<Solver> createSolver(Graph &graph, Vehicle &vehicle, std::list<Route> &routes,
                                                AlgorithmType algorithmType);
};


#endif //SOLVER_HELPER_H
