//
// Created by petkovic on 27.03.25.
//

#ifndef ROUTE_H
#define ROUTE_H

#include <array>
#include <iostream>
#include <cstdint>

class Route {
public:
    Route();

    virtual ~Route();

    void addNode(uint16_t id);

    void printRoute() const;

    static constexpr uint8_t MAX_COUNT_NODES_PER_ROUTE = 20;

    std::array<short, 20> getNodes() const;

private:
    std::array<short, MAX_COUNT_NODES_PER_ROUTE> nodes;
    uint8_t size = 0; // track number of nodes added
};


#endif //ROUTE_H
