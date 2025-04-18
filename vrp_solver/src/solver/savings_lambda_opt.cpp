//
// Created by petkovic on 15.04.25.
//

#include <solver/savings_lambda_opt.h>

SavingsLambdaOpt::SavingsLambdaOpt(Graph &graph, Vehicle &vehicle, std::list<Route> &r)
    : Solver(graph, vehicle, r),
      _savings_clark_wright(graph, vehicle, r),
      _lambda_opt(graph, vehicle, r) {
}

void SavingsLambdaOpt::solve() {
    _savings_clark_wright.solve();
    _lambda_opt.solve();
}
