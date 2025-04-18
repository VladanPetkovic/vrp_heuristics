//
// Created by petkovic on 15.04.25.
//

#ifndef LAMBDA_OPT_SAVINGS_H
#define LAMBDA_OPT_SAVINGS_H

#include <solver/solver.h>
#include <solver/savings_clark_wright.h>
#include <solver/lambda_opt.h>

class SavingsLambdaOpt : public Solver {
public:
    SavingsLambdaOpt(Graph &graph, Vehicle &vehicle, std::list<Route> &r);

    void solve() override;

private:
    SavingsClarkWright _savings_clark_wright;
    LambdaOpt _lambda_opt;
};


#endif //LAMBDA_OPT_SAVINGS_H
