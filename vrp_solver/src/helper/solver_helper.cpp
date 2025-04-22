//
// Created by petkovic on 01.04.25.
//

#include <helper/solver_helper.h>

std::unique_ptr<Solver> SolverHelper::createSolver(Graph &graph, Vehicle &vehicle, std::list<Route> &routes,
                                                   const AlgorithmType algorithmType) {
    switch (algorithmType) {
        case AlgorithmType::NearestNeighbor:
            return std::make_unique<NearestNeighbor>(graph, vehicle, routes);
        case AlgorithmType::SavingsClarkWright:
            return std::make_unique<SavingsClarkWright>(graph, vehicle, routes);
        case AlgorithmType::NNLambdaOpt:
            return std::make_unique<NNLambdaOpt>(graph, vehicle, routes);
        case AlgorithmType::SavingsLambdaOpt:
            return std::make_unique<SavingsLambdaOpt>(graph, vehicle, routes);
        case AlgorithmType::NNImprovement:
            return std::make_unique<NNImprovement>(graph, vehicle, routes);
        case AlgorithmType::SavingsImprovement:
            return std::make_unique<SavingsImprovement>(graph, vehicle, routes);
        case AlgorithmType::IteratedLocalSearch:
            return std::make_unique<IteratedLocalSearch>(graph, vehicle, routes);
    }
    throw std::invalid_argument("Unknown algorithm");
}
