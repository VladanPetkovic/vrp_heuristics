//
// Created by petkovic on 26.03.25.
//

#ifndef NODE_H
#define NODE_H
#include <cstdint>


class Node {
public:
    Node() : x_position(0), y_position(0), quantity(0), id(0), type(0), next(nullptr) {
    }

    Node(uint16_t x, uint16_t y, uint16_t id, uint8_t type);

    virtual ~Node();

    uint16_t getX() const;

    uint16_t getY() const;

    uint8_t getQuantity() const;

    uint16_t getId() const;

    uint8_t getType() const;

    Node *getNext() const;

    void setNext(Node *node);

    void setQuantity(uint8_t quantity);

private:
    // TODO: struct Position
    uint16_t x_position;
    uint16_t y_position;
    uint8_t quantity;
    uint16_t id;
    uint8_t type;
    Node *next;
};


#endif //NODE_H
