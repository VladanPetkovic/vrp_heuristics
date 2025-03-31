//
// Created by petkovic on 26.03.25.
//

#include <models/vehicle.h>

Vehicle::Vehicle() {
    // ctor
}

bool Vehicle::exceedsCapacity(uint16_t to_compare) const {
    return to_compare > capacity;
}

uint16_t Vehicle::getCapacity() const {
    return capacity;
}

Node &Vehicle::getDepartureNode() {
    return departureNode;
}

Node &Vehicle::getArrivalNode() {
    return arrivalNode;
}

void Vehicle::setCapacity(const uint16_t capacity) {
    this->capacity = capacity;
}

void Vehicle::setDepartureNode(const Node *node) {
    this->departureNode = *node;
}

void Vehicle::setArrivalNode(const Node *node) {
    this->arrivalNode = *node;
}
