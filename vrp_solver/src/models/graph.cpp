//
// Created by petkovic on 24.03.25.
//

#include "models/graph.h"


void Graph::addNode(u_int16_t id, const Node &node) {
    nodes[id] = node;
}

Node *Graph::getNode(u_int16_t id) {
    return &nodes.at(id);
}

// void Graph::addEdge(int from, int to) {
//     edges.emplace_back(from, to);
// }

u_int16_t Graph::getNumNodes() const {
    return nodes.size();
}

void Graph::printGraph() const {
    std::cout << "Nodes:\n";
    for (const auto &[id, node]: nodes) {
        std::cout << id << ": " << node.getId()
                << " x: " << node.getX()
                << " y: " << node.getY()
                << " quantity: " << static_cast<int>(node.getQuantity()) << "\n";
    }
}

double Graph::getDistance(const uint16_t from, const uint16_t to) const {
    if (distanceMatrix.contains(from)) {
        if (distanceMatrix.at(from).contains(to)) {
            return distanceMatrix.at(from).at(to);
        }
    } else {
        if (distanceMatrix.at(to).contains(from)) {
            // saving only one direction, but both can be passed
            return distanceMatrix.at(to).at(from);
        }
    }
    return std::numeric_limits<double>::max();
}

/**
 * key value pair:
 * node.first is the id
 * node.second is the node
 */
void Graph::computeDistances() {
    for (const auto &node1: nodes) {
        for (const auto &node2: nodes) {
            u_int16_t id1 = node1.first;
            u_int16_t id2 = node2.first;
            if (id1 < id2) {
                double dist = std::sqrt(
                    std::pow(node1.second.getX() - node2.second.getX(), 2) +
                    std::pow(node1.second.getY() - node2.second.getY(), 2)
                );
                distanceMatrix[id1][id2] = dist;
            }
        }
    }
}
