#pragma once


#include "MovesNode.h"

class MovesList {
public:
    MovesList() {
        head = nullptr;
        tail = nullptr;
    }


    MovesNode* getTail() const;
    MovesNode* getHead() const;
    moves popHead();
    void addToHead(MovesNode* node);
    void addToTail(MovesNode* node);
    void addMove(moves move);
    void remove(MovesNode** node);


private:
    MovesNode* head = nullptr;
    MovesNode* tail = nullptr;
    void removeFromTail();
    void removeFromHead();
    void removeFromMiddle(MovesNode* node);
};
