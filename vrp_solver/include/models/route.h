//
// Created by petkovic on 27.03.25.
//

#ifndef ROUTE_H
#define ROUTE_H

#include <array>
#include <iostream>
#include <models/graph.h>
#include <models/vehicle.h>
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

    void removeNodeFrom(uint8_t index);

    uint8_t findNodeIndex(uint16_t id) const;

    void printRoute() const;

    uint16_t getTotalQuantity(Graph &graph) const;

    double getTotalDistance(const Graph &graph, Vehicle &vehicle) const;

    uint16_t getTotalQuantity() const;

    void setTotalQuantity(double new_total_quantity);

    uint8_t getSize() const;

    bool isEmpty() const;

    bool operator==(const Route &route) const;

    bool hasNode(uint16_t id) const;

    bool startsWith(uint16_t id) const;

    bool endsWith(uint16_t id) const;

    void removeFirst();

    void removeLast();

    std::array<short, MAX_COUNT_NODES_PER_ROUTE> getNodes() const;

    short getNodeIdAt(uint8_t index) const;

    void setNodeIdAt(const uint8_t index, const short id);

private:
    std::array<short, MAX_COUNT_NODES_PER_ROUTE> nodes;
    uint8_t size = 0; // track the number of nodes added
    double total_quantity = 0;
};


#endif //ROUTE_H
