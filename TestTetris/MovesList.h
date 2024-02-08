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
    void addToHead(MovesNode* node);
    void addToTail(MovesNode* node);
    void remove(MovesNode** node);


private:
    MovesNode* head = nullptr;
    MovesNode* tail = nullptr;
    void removeFromTail();
    void removeFromHead();
    void removeFromMiddle(MovesNode* node);
};
