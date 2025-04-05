//
// Created by petkovic on 01.04.25.
//

#include <helper/solver_helper.h>

std::unique_ptr<Solver> SolverHelper::createSolver(Graph &graph, Vehicle &vehicle, const AlgorithmType algorithmType) {
    switch (algorithmType) {
        case AlgorithmType::NearestNeighbor:
            return std::make_unique<NearestNeighbor>(graph, vehicle);
        case AlgorithmType::SavingsClarkWright:
            return std::make_unique<SavingsClarkWright>(graph, vehicle);
    }
    throw std::invalid_argument("Unknown algorithm");
}
