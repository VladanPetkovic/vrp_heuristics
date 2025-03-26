//
// Created by petkovic on 24.03.25.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <models/node.h>

class Graph {
public:
    void addNode(int id, const Node &node);

    Node *getNode(int id);

    void addEdge(int from, int to);

    void printGraph() const;

private:
    std::unordered_map<int, Node> nodes; // TODO save as pointer
    std::vector<std::pair<int, int> > edges;
};

#endif //GRAPH_H
