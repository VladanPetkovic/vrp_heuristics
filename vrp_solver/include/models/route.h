//
// Created by petkovic on 27.03.25.
//

#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <cstdint>
#include <models/node.h>

class Route {
public:
    Route() : head(nullptr), tail(nullptr) {
    }

    virtual ~Route();

    void addNode(Node *node);

    void printRoute() const;

private:
    Node *head;
    Node *tail;
};


#endif //ROUTE_H
