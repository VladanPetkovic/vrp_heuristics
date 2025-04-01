//
// Created by petkovic on 24.03.25.
//

#ifndef XML_CONVERTER_H
#define XML_CONVERTER_H

#include <models/graph.h>
#include <list>
#include <lib/pugixml.hpp>
#include <string>
#include <cstdint>
#include <models/route.h>
#include <models/vehicle.h>
#include <models/node.h>

class XMLConverter {
public:
    static void loadGraphFromData(Graph &graph, Vehicle &vehicle, const std::string &filename);

    static bool saveSolutionToFile(std::list<Route> &routes, Graph &graph, const std::string &filename);
};

#endif //XML_CONVERTER_H
