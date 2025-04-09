//
// Created by petkovic on 27.03.25.
//

#ifndef SOLVER_H
#define SOLVER_H

#include <list>
#include <models/vehicle.h>

#include <models/graph.h>
#include <models/route.h>

class Solver {
public:
    Solver(Graph &graph, Vehicle &vehicle) : graph(graph), vehicle(vehicle) {
    }

    // "using virtual for a correct destructor-chain"
    // at first, the child is called, then the parent is called when using virtual
    virtual ~Solver();

    virtual void solve() = 0;

    virtual int getIterations() const;

    virtual void printRoutes() const;

    std::list<Route> &getRoutes();

protected:
    Graph &graph;
    Vehicle &vehicle;
    std::list<Route> routes;
};


#endif //SOLVER_H
