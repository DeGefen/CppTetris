#ifndef TETRIS_LISTNODE_H
#define TETRIS_LISTNODE_H

#include "Line.h"

class ListNode {
public:
    ListNode() { setNewNode(); }
    Line* line;
    ListNode* next = nullptr;
    ListNode* prev = nullptr;
    void setNewNode();
    void deleteNode();
};

#endif //TETRIS_LISTNODE_H
