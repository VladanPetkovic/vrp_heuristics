//
// Created by petkovic on 27.03.25.
//

#ifndef ROUTE_H
#define ROUTE_H

#include <array>
#include <iostream>
#include <models/graph.h>
#include <cstdint>

class Route {
public:
    Route();

    virtual ~Route();

    void addNode(uint16_t id);

    void printRoute() const;

    uint16_t getTotalQuantity(Graph &graph) const;

    bool hasNode(uint16_t id) const;

    bool startsWith(uint16_t id) const;

    bool endsWith(uint16_t id) const;

    void removeFirst();

    void removeLast();

    static constexpr uint8_t MAX_COUNT_NODES_PER_ROUTE = 50;

    std::array<short, MAX_COUNT_NODES_PER_ROUTE> getNodes() const;

private:
    std::array<short, MAX_COUNT_NODES_PER_ROUTE> nodes;
    uint8_t size = 0; // track number of nodes added
};


#endif //ROUTE_H
