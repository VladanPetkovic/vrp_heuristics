//
// Created by petkovic on 21.04.25.
//

#ifndef ITERATED_LOCAL_SEARCH_H
#define ITERATED_LOCAL_SEARCH_H

#include <solver/solver.h>
#include <solver/inter_route_improvement.h>
#include <solver/lambda_opt.h>
#include <solver/savings_clark_wright.h>
#include <random>

class IteratedLocalSearch : public Solver {
public:
    IteratedLocalSearch(Graph &graph, Vehicle &vehicle, std::list<Route> &r);

    void solve() override;

    int getIterations() const override;

    const int MAX_ITERATIONS = 200000;

    const double ALPHA = 0.965;

private:
    SavingsClarkWright _savings_clark_wright;
    InterRouteImprovement _inter_route_improvement;
    LambdaOpt _lambda_opt;
    int _iterations = 0;
    double temperature = 1000.0;

    void initSolution();

    void localSearch();

    void shake(uint8_t intensity);

    void randomIntraSwap();

    void randomInterMove();

    void randomCrossExchange();

    bool accept(std::list<Route> &current, double new_cost) const;
};


#endif //ITERATED_LOCAL_SEARCH_H
