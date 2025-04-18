//
// Created by petkovic on 18.04.25.
//

#ifndef NN_IMPROVEMENT_H
#define NN_IMPROVEMENT_H

#include <solver/solver.h>
#include <solver/inter_route_improvement.h>
#include <solver/lambda_opt.h>
#include <solver/nearest_neighbor.h>

class NNImprovement : public Solver {
public:
    NNImprovement(Graph &graph, Vehicle &vehicle, std::list<Route> &r);

    void solve() override;

private:
    NearestNeighbor _nearest_neighbor;
    InterRouteImprovement _inter_route_improvement;
    LambdaOpt _lambda_opt;
};


#endif //NN_IMPROVEMENT_H
