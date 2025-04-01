//
// Created by petkovic on 01.04.25.
//

#include <helper/solver_helper.h>

std::unique_ptr<Solver> SolverHelper::createSolver(Graph &graph, Vehicle &vehicle, const std::string &algorithm) {
    if (algorithm == "nearest") {
        return std::make_unique<NearestNeighbor>(graph, vehicle);
    }
    throw std::invalid_argument("Unknown algorithm: " + algorithm);
}
