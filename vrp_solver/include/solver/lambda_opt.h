//
// Created by petkovic on 14.04.25.
//

#ifndef LAMBDA_OPT_H
#define LAMBDA_OPT_H

#include <solver/solver.h>

class LambdaOpt : public Solver {
public:
    LambdaOpt(Graph &graph, Vehicle &vehicle) : Solver(graph, vehicle) {
    }

    void solve() override;

    const uint8_t MAX_ITERATIONS = 100;

private:
    void reconnectEdges(Route &route);
};


#endif //LAMBDA_OPT_H
