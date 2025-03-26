//
// Created by petkovic on 24.03.25.
//

#include "graph.h"


void Graph::addNode(int id, const std::string &label) {
    nodes[id] = label;
}

void Graph::addEdge(int from, int to) {
    edges.emplace_back(from, to);
}

void Graph::printGraph() const {
    std::cout << "Nodes:\n";
    for (const auto &[id, label]: nodes)
        std::cout << id << ": " << label << "\n";

    std::cout << "Edges:\n";
    for (const auto &[from, to]: edges)
        std::cout << from << " -> " << to << "\n";
}
