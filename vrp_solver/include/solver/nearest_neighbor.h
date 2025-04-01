//
// Created by petkovic on 01.04.25.
//

#ifndef NEAREST_NEIGHBOR_H
#define NEAREST_NEIGHBOR_H

#include <solver/solver.h>

class NearestNeighbor : public Solver {
public:
    NearestNeighbor(Graph &graph, Vehicle &vehicle) : Solver(graph, vehicle) {
    }

    void solve() override;

private:
    bool allNodesVisited(const std::vector<bool> &visited);

    Route buildRoute(uint16_t start_node_id, std::vector<bool> &visited) const;

    uint16_t findNearestNode(uint16_t current_node_id, const std::vector<bool> &visited) const;
};

#endif //NEAREST_NEIGHBOR_H
