//
// Created by petkovic on 18.04.25.
//

#include <solver/nn_improvement.h>

NNImprovement::NNImprovement(Graph &graph, Vehicle &vehicle, std::list<Route> &r)
    : Solver(graph, vehicle, r),
      _nearest_neighbor(graph, vehicle, r),
      _inter_route_improvement(graph, vehicle, r),
      _lambda_opt(graph, vehicle, r) {
}

void NNImprovement::solve() {
    _nearest_neighbor.solve();
    _lambda_opt.solve();
    _inter_route_improvement.solve();
}
