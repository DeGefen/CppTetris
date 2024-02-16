#ifndef TETRIS_LISTNODE_H
#define TETRIS_LISTNODE_H

#include "Line.h"

class ListNode {
    void setNewNode();
public:
    ListNode() { setNewNode(); }
    ListNode(const ListNode& node) = delete;
    ListNode operator=(const ListNode& node) = delete;
    ListNode* operator=(const ListNode* node) = delete;
    ~ListNode() { (deleteNode()); }

    void deleteNode();


    Line* line;
    ListNode* next = nullptr;
    ListNode* prev = nullptr;
};

#endif //TETRIS_LISTNODE_H
