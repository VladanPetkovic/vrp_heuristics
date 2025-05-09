//
// Created by petkovic on 18.04.25.
//

#ifndef INTER_ROUTE_IMPROVEMENT_H
#define INTER_ROUTE_IMPROVEMENT_H

#include <solver/solver.h>
#include <models/route.h>

class InterRouteImprovement : public Solver {
public:
    InterRouteImprovement(Graph &graph, Vehicle &vehicle, std::list<Route> &r) : Solver(graph, vehicle, r) {
    }

    void solve() override;

    int getIterations() const override;

    const uint8_t MAX_ITERATIONS = 100;

    const uint8_t MAX_LAMBDA = 2;

private:
    int _iterations = 0;

    void reconnectEdges(Route &route, Route &neighbor_route);

    void trySwap(std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &new_route,
                 std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &new_neighbor,
                 uint8_t i, uint8_t j, uint8_t lambda, bool &improvement);

    void tryInsert(std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &new_route,
                   std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &new_neighbor,
                   uint8_t i, uint8_t j, uint8_t lambda, bool &improvement,
                   uint8_t &size, uint8_t &neighbor_size);

    void tryTwoOptStar(std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &new_route,
                       std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &new_neighbor,
                       uint8_t i, uint8_t j, bool &improvement,
                       uint8_t &size, uint8_t &neighbor_size);

    double getRouteCost(const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route) const;

    bool isFeasible(const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route) const;

    // bool hasInvalidNode(std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route) const;
};


#endif //INTER_ROUTE_IMPROVEMENT_H
