//
// Created by petkovic on 24.03.25.
//

#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "graph.h"
#include <string>
#include <fstream>

class GraphBuilder {
public:
    static void loadGraphFromData(Graph& graph, const std::string& filename);
};

#endif //GRAPHBUILDER_H
