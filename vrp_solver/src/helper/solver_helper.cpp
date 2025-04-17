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
        case AlgorithmType::LambdaOptNN:
            return std::make_unique<LambdaOptNN>(graph, vehicle);
        case AlgorithmType::LambdaOptSavings:
            return std::make_unique<LambdaOptSavings>(graph, vehicle);
        // case AlgorithmType::LambdaInterchangeNN:
        //     return std::make_unique<LambdaInterchangeNN>(graph, vehicle);
        case AlgorithmType::LambdaInterchangeSavings:
            return std::make_unique<LambdaInterchangeSavings>(graph, vehicle);
    }
    throw std::invalid_argument("Unknown algorithm");
}
