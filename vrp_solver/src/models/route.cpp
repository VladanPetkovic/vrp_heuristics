//
// Created by petkovic on 27.03.25.
//

#include <models/route.h>

Route::~Route() {
    RouteNode *current = head;
    while (current) {
        RouteNode *temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
}

void Route::addNode(uint16_t id) {
    auto *newNode = new RouteNode{id, nullptr};
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void Route::printRoute() const {
    RouteNode *current = head;
    while (current) {
        std::cout << current->id << " -> ";
        current = current->next;
    }
    std::cout << "End\n";
}

RouteNode *Route::getHead() const {
    return head;
}
