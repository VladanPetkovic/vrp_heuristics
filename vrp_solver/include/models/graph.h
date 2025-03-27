//
// Created by petkovic on 24.03.25.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <models/node.h>

class Graph {
public:
    void addNode(u_int16_t id, const Node &node);

    Node *getNode(u_int16_t id);

    u_int16_t getNumNodes() const;

    void computeDistances();

    double getDistance(u_int16_t from, uint16_t to) const;

    // void addEdge(int from, int to);

    void printGraph() const;

private:
    std::unordered_map<u_int16_t, Node> nodes; // TODO save as pointer
    // std::vector<std::pair<int, int> > edges;
    std::unordered_map<u_int16_t, std::unordered_map<u_int16_t, double> > distanceMatrix;
};

#endif //GRAPH_H
