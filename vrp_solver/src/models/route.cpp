//
// Created by petkovic on 27.03.25.
//

#include <models/route.h>

Route::~Route() {
    // dtor
}

void Route::addNode(Node *node) {
    if (!head) {
        head = tail = node;
    } else {
        tail->setNext(node);
        tail = node;
    }
}

void Route::printRoute() const {
    Node *current = head;
    while (current) {
        std::cout << current->getId() << " -> ";
        current = current->getNext();
    }
    std::cout << "End\n";
}
