//
// Created by petkovic on 24.03.25.
//

#include <models/graph.h>


void Graph::addNode(uint16_t id, const Node &node) {
    nodes[id] = node;
}

Node *Graph::getNode(uint16_t id) {
    return &nodes.at(id);
}

// void Graph::addEdge(int from, int to) {
//     edges.emplace_back(from, to);
// }

uint16_t Graph::getNumNodes() const {
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
    if (from == to) {
        return 0.0;
    }
    if (from == -1 || to == -1) {
        std::cout << "invalid distance" << std::endl;
        return 0.0;
    }

    uint16_t newFrom = to;
    uint16_t newTo = from;
    if (from > to) {
        return distanceMatrix.at(newFrom).at(newTo);
    }

    return distanceMatrix.at(from).at(to);
}

/**
 * key value pair:
 * node.first is the id
 * node.second is the node
 */
void Graph::computeDistances() {
    for (const auto &node1: nodes) {
        for (const auto &node2: nodes) {
            uint16_t id1 = node1.first;
            uint16_t id2 = node2.first;
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
