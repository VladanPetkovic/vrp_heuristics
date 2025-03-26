//
// Created by petkovic on 24.03.25.
//

#include "models/graph.h"


void Graph::addNode(int id, const Node &node) {
    nodes[id] = node;
}

Node *Graph::getNode(int id) {
    return &nodes.at(id);
}

void Graph::addEdge(int from, int to) {
    edges.emplace_back(from, to);
}

void Graph::printGraph() const {
    std::cout << "Nodes:\n";
    for (const auto &[id, node]: nodes) {
        std::cout << id << ": " << node.getId()
                << " x: " << node.getX()
                << " y: " << node.getY()
                << " quantity: " << static_cast<int>(node.getQuantity()) << "\n";
    }

    std::cout << "Edges:\n";
    for (const auto &[from, to]: edges) {
        std::cout << from << " -> " << to << "\n";
    }
}
