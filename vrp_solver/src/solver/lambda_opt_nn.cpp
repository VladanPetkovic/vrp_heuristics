//
// Created by petkovic on 14.04.25.
//

#include <solver/lambda_opt_nn.h>

LambdaOptNN::LambdaOptNN(Graph &graph, Vehicle &vehicle)
    : Solver(graph, vehicle),
      _nearestNeighbor(graph, vehicle),
      _lambda_opt(graph, vehicle) {
}

void LambdaOptNN::solve() {
    _nearestNeighbor.solve();
    auto& nn_routes = _nearestNeighbor.getRoutes();
    _lambda_opt.setRoutes(nn_routes);
    _lambda_opt.solve();
    auto& lambda_opt_routes = _lambda_opt.getRoutes();
    this->routes = lambda_opt_routes;
}
