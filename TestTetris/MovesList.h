#pragma once


#include "MovesNode.h"

class MovesList {
public:
    MovesList() {
        head = nullptr;
        tail = nullptr;
    }
    ~MovesList() { empty(); }

    MovesList operator=(MovesList& movesList) {
        head = movesList.head;
        tail = movesList.tail;
        movesList.head = nullptr;
        movesList.tail = nullptr;
    }

    MovesNode::moves popHead();
    void addToHead(MovesNode* node);
    void addToTail(MovesNode* node);
    void addMove(MovesNode::moves move);
    void removeFromTail();
    bool isEmpty() const;
    void empty();


private:
    MovesNode* head = nullptr;
    MovesNode* tail = nullptr;
    void removeFromHead();
};
