//
// Created by petkovic on 26.03.25.
//

#include <models/node.h>

Node::Node(const uint16_t x, const uint16_t y, const uint16_t id, const uint8_t type)
    : x_position(x), y_position(y), quantity(0), id(id), type(type) {
}

Node::~Node() {
    // dtor
}

uint16_t Node::getX() const {
    return x_position;
}

uint16_t Node::getY() const {
    return y_position;
}

uint8_t Node::getQuantity() const {
    return quantity;
}

uint16_t Node::getId() const {
    return id;
}

uint8_t Node::getType() const {
    return type;
}

Node *Node::getNext() const {
    return next;
}

void Node::setNext(Node *node) {
    next = node;
}

void Node::setQuantity(const uint8_t quantity) {
    this->quantity = quantity;
}
