//
// Created by petkovic on 27.03.25.
//

#include <models/route.h>

Route::Route() {
    // ctor
    nodes.fill(-1); // setting all nodes to default
}

Route::~Route() {
    // dtor
}

void Route::addNode(const uint16_t id) {
    if (size < MAX_COUNT_NODES_PER_ROUTE) {
        nodes[size++] = id;
    } else {
        std::cerr << "Route is full! Cannot add more nodes.\n";
    }
}

void Route::printRoute() const {
    for (uint16_t i = 0; i < size; i++) {
        std::cout << nodes[i] << " ";
    }
    std::cout << "End\n";
}

std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> Route::getNodes() const {
    return nodes;
}
