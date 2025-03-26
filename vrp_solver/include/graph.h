//
// Created by petkovic on 24.03.25.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

class Graph {
public:
    void addNode(int id, const std::string &label);

    void addEdge(int from, int to);

    void printGraph() const;

private:
    std::unordered_map<int, std::string> nodes;
    std::vector<std::pair<int, int> > edges;
};

#endif //GRAPH_H
