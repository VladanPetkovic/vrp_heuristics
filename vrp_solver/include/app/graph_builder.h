//
// Created by petkovic on 24.03.25.
//

#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <models/graph.h>
#include <lib/pugixml.hpp>
#include <string>
#include <cstdint>
#include <models/vehicle.h>

class GraphBuilder {
public:
    static void loadGraphFromData(Graph &graph, Vehicle &vehicle, const std::string &filename);
};

#endif //GRAPHBUILDER_H
