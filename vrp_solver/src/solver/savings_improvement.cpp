//
// Created by petkovic on 16.04.25.
//

#include <solver/savings_improvement.h>

SavingsImprovement::SavingsImprovement(Graph &graph, Vehicle &vehicle, std::list<Route> &r)
    : Solver(graph, vehicle, r),
      _savings_clark_wright(graph, vehicle, r),
      _inter_route_improvement(graph, vehicle, r),
      _lambda_opt(graph, vehicle, r) {
}

void SavingsImprovement::solve() {
    _savings_clark_wright.solve();
    _lambda_opt.solve();
    _inter_route_improvement.solve();
}
