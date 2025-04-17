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

void Route::setRoute(const std::array<short, MAX_COUNT_NODES_PER_ROUTE> &newRoute) {
    uint8_t newRouteSize = 0;
    for (uint8_t i = 0; i < newRoute.size() && newRoute[i] != -1; i++) {
        newRouteSize++;
    }

    // reset route
    nodes.fill(-1);
    size = 0;

    // add nodes
    for (const auto node_id: newRoute) {
        if (node_id != -1) {
            addNode(node_id);
        }
    }
}

void Route::addNode(const uint16_t id) {
    uint8_t count = 0;
    uint16_t depot_id = nodes[0];

    for (auto i = 0; i < size; i++) {
        if (nodes[i] == id) {
            count++;
        }
    }
    if (count >= 2) {
        return; // only depot can be inserted two times
    }

    if (size < MAX_COUNT_NODES_PER_ROUTE) {
        if (size >= 3) {
            // depot at end
            if (depot_id == nodes[size - 1]) {
                nodes[size - 1] = id;
                nodes[size] = depot_id;
                size++;
            } else {
                // depot not at end
                nodes[size++] = id;
            }
        } else {
            nodes[size++] = id;
        }
    } else {
        std::cerr << "Route is full! Cannot add more nodes.\n";
    }
}

void Route::addNodeToFront(const uint16_t id) {
    if (size >= MAX_COUNT_NODES_PER_ROUTE) {
        std::cerr << "Route is full! Cannot add node to front.\n";
        return;
    }

    for (auto i = size; i > 0; --i) {
        nodes[i] = nodes[i - 1];
    }
    nodes[1] = id; // the first one is always the depot
    ++size;
}

void Route::insertNodeAt(uint8_t index, uint16_t id) {
    if (size >= MAX_COUNT_NODES_PER_ROUTE || index > size) {
        std::cerr << "Invalid index or route full!\n";
        return;
    }
    for (auto i = size; i > index; --i) {
        nodes[i] = nodes[i - 1];
    }
    nodes[index] = id;
    ++size;
}

uint8_t Route::findNodeIndex(uint16_t id) const {
    for (uint8_t i = 0; i < size; ++i) {
        if (nodes[i] == id) {
            return i;
        }
    }
    return -1; // not found
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

bool Route::isEmpty() const {
    return size == 0;
}

bool Route::operator==(const Route &route) const {
    if (this->size != route.size) {
        return false;
    }
    for (uint8_t i = 0; i < size; ++i) {
        if (this->nodes[i] != route.nodes[i]) {
            return false;
        }
    }
    return true;
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
