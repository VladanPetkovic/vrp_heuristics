//
// Created by petkovic on 16.04.25.
//

#ifndef LAMBDA_INTERCHANGE_H
#define LAMBDA_INTERCHANGE_H

#include <solver/solver.h>
#include <models/route.h>

class LambdaInterchange : public Solver {
public:
    LambdaInterchange(Graph &graph, Vehicle &vehicle) : Solver(graph, vehicle) {
    }

    void solve() override;

    const uint8_t MAX_ITERATIONS = 100;

private:
    void reconnectEdges(Route &route, Route &neighbor_route);

    double getRouteCost(const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route);

    bool isFeasible(const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route);
};


#endif //LAMBDA_INTERCHANGE_H
