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

uint16_t Route::getTotalQuantity(Graph &graph) const {
    uint16_t total = 0;
    for (uint16_t i = 0; i < size; i++) {
        total += graph.getNode(nodes[i])->getQuantity();
    }
    return total;
}

uint8_t Route::getSize() const {
    return size;
}

bool Route::hasNode(uint16_t node_id) const {
    for (uint8_t i = 0; i < size; ++i) {
        if (nodes[i] == node_id) {
            return true;
        }
    }
    return false;
}

// depot is at first place, but we are interested in the first customer
bool Route::startsWith(uint16_t node_id) const {
    return size >= 2 && nodes[1] == node_id;
}

// same here
bool Route::endsWith(uint16_t node_id) const {
    return size >= 2 && nodes[size - 2] == node_id;
}

void Route::removeFirst() {
    if (size == 0) {
        return;
    }
    for (uint8_t i = 1; i < size; ++i) {
        nodes[i - 1] = nodes[i];
    }
    --size;
}

void Route::removeLast() {
    if (size == 0) {
        return;
    }
    --size;
}

std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> Route::getNodes() const {
    return nodes;
}
