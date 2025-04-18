//
// Created by petkovic on 14.04.25.
//

#include <solver/nn_lambda_opt.h>

NNLambdaOpt::NNLambdaOpt(Graph &graph, Vehicle &vehicle, std::list<Route> &r)
    : Solver(graph, vehicle, r),
      _nearestNeighbor(graph, vehicle, r),
      _lambda_opt(graph, vehicle, r) {
}

void NNLambdaOpt::solve() {
    _nearestNeighbor.solve();
    _lambda_opt.solve();
}
