//
// Created by petkovic on 16.04.25.
//

#ifndef LAMBDA_INTERCHANGE_SAVINGS_H
#define LAMBDA_INTERCHANGE_SAVINGS_H

#include <solver/solver.h>
#include <solver/inter_route_improvement.h>
#include <solver/lambda_opt.h>
#include <solver/savings_clark_wright.h>

class SavingsImprovement : public Solver {
public:
    SavingsImprovement(Graph &graph, Vehicle &vehicle, std::list<Route> &r);

    void solve() override;

private:
    SavingsClarkWright _savings_clark_wright;
    InterRouteImprovement _inter_route_improvement;
    LambdaOpt _lambda_opt;
};


#endif //LAMBDA_INTERCHANGE_SAVINGS_H
