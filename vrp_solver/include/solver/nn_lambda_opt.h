//
// Created by petkovic on 14.04.25.
//

#ifndef LAMBDA_OPT_NN_H
#define LAMBDA_OPT_NN_H

#include <solver/solver.h>
#include <solver/nearest_neighbor.h>
#include <solver/lambda_opt.h>


class NNLambdaOpt : public Solver {
public:
    NNLambdaOpt(Graph &graph, Vehicle &vehicle, std::list<Route> &r);

    void solve() override;

private:
    NearestNeighbor _nearestNeighbor;
    LambdaOpt _lambda_opt;
};


#endif //LAMBDA_OPT_NN_H
