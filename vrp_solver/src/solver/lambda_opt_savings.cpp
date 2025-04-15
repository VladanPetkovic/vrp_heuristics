//
// Created by petkovic on 15.04.25.
//

#include <solver/lambda_opt_savings.h>

LambdaOptSavings::LambdaOptSavings(Graph &graph, Vehicle &vehicle)
    : Solver(graph, vehicle),
      _savings_clark_wright(graph, vehicle),
      _lambda_opt(graph, vehicle) {
}

void LambdaOptSavings::solve() {
    _savings_clark_wright.solve();
    auto &savings_routes = _savings_clark_wright.getRoutes();
    _lambda_opt.setRoutes(savings_routes);
    _lambda_opt.solve();
    auto &lambda_opt_routes = _lambda_opt.getRoutes();
    this->routes = lambda_opt_routes;
}
