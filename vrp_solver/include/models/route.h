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

    static constexpr uint8_t MAX_COUNT_NODES_PER_ROUTE = 64;

    void setRoute(const std::array<short, MAX_COUNT_NODES_PER_ROUTE> &newRoute);

    void addNode(uint16_t id);

    void addNodeToFront(uint16_t id);

    void insertNodeAt(uint8_t index, uint16_t id);

    uint8_t findNodeIndex(uint16_t id) const;

    void printRoute() const;

    uint16_t getTotalQuantity(Graph &graph) const;

    uint8_t getSize() const;

    bool isEmpty() const;

    bool operator==(const Route &route) const;

    bool hasNode(uint16_t id) const;

    bool startsWith(uint16_t id) const;

    bool endsWith(uint16_t id) const;

    void removeFirst();

    void removeLast();

    std::array<short, MAX_COUNT_NODES_PER_ROUTE> getNodes() const;

private:
    std::array<short, MAX_COUNT_NODES_PER_ROUTE> nodes;
    uint8_t size = 0; // track number of nodes added
};


#endif //ROUTE_H
