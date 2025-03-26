//
// Created by petkovic on 24.03.25.
//

#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "models/graph.h"
#include "lib/pugixml.hpp"
#include <string>
#include <cstdint>

class GraphBuilder {
public:
    static void loadGraphFromData(Graph &graph, const std::string &filename);
};

#endif //GRAPHBUILDER_H
