//
// Created by petkovic on 27.03.25.
//

#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <cstdint>

struct RouteNode {
    uint16_t id;
    RouteNode *next;
};

class Route {
public:
    Route() : head(nullptr), tail(nullptr) {
    }

    virtual ~Route();

    void addNode(uint16_t id);

    void printRoute() const;

    RouteNode *getHead() const;

private:
    RouteNode *head;
    RouteNode *tail;
};


#endif //ROUTE_H
