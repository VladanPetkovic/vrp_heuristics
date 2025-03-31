//
// Created by petkovic on 26.03.25.
//

#ifndef VEHICLE_H
#define VEHICLE_H
#include <cstdint>

#include <models/node.h>

class Vehicle {
public:
    Vehicle();

    bool exceedsCapacity(uint16_t to_compare) const;

    uint16_t getCapacity() const;

    Node &getDepartureNode();

    Node &getArrivalNode();

    void setCapacity(uint16_t capacity);

    void setDepartureNode(const Node *node);

    void setArrivalNode(const Node *node);

private:
    uint16_t capacity{};
    Node departureNode;
    Node arrivalNode;
};


#endif //VEHICLE_H
