//
// Created by petkovic on 16.04.25.
//

#ifndef LAMBDA_INTERCHANGE_SAVINGS_H
#define LAMBDA_INTERCHANGE_SAVINGS_H

#include <solver/solver.h>
#include <solver/lambda_interchange.h>
#include <solver/lambda_opt.h>
#include <solver/savings_clark_wright.h>

class LambdaInterchangeSavings : public Solver {
public:
    LambdaInterchangeSavings(Graph &graph, Vehicle &vehicle);

    void solve() override;

private:
    SavingsClarkWright _savings_clark_wright;
    LambdaInterchange _lambda_interchange;
    LambdaOpt _lambda_opt;
};


#endif //LAMBDA_INTERCHANGE_SAVINGS_H
