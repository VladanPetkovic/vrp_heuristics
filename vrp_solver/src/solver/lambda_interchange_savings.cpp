//
// Created by petkovic on 16.04.25.
//

#include <solver/lambda_interchange_savings.h>

LambdaInterchangeSavings::LambdaInterchangeSavings(Graph &graph, Vehicle &vehicle)
    : Solver(graph, vehicle),
      _savings_clark_wright(graph, vehicle),
      _lambda_interchange(graph, vehicle),
      _lambda_opt(graph, vehicle) {
}

void LambdaInterchangeSavings::solve() {
    _savings_clark_wright.solve();
    auto &savings_routes = _savings_clark_wright.getRoutes();

    _lambda_opt.setRoutes(savings_routes);
    _lambda_opt.solve();
    auto &lambda_opt_routes = _lambda_opt.getRoutes();

    _lambda_interchange.setRoutes(lambda_opt_routes);
    _lambda_interchange.solve();
    auto &lambda_interchange_routes = _lambda_interchange.getRoutes();

    this->routes = lambda_interchange_routes;
}
