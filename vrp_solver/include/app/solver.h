//
// Created by petkovic on 27.03.25.
//

#ifndef SOLVER_H
#define SOLVER_H

#include "models/graph.h"
#include "models/route.h"

class Solver {
public:
    explicit Solver(Graph &graph) : graph(graph) {
    }

    void nearestNeighbor(u_int16_t startNodeId);

    void printRoutes() const;

private:
    Graph &graph;
    std::vector<Route> routes;
};


#endif //SOLVER_H
