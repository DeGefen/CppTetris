#pragma once
//
// Created by Eylon Serok on 07/01/2024.
//

#include "ListNode.h"

#ifndef TETRIS_Board_H
#define TETRIS_Board_H

#endif //TETRIS_Board_H

class Board {
public:
    ListNode* head;
    ListNode* tail;
    int nodesCount;
    void addToHead(ListNode* node);
    void addToTail(ListNode* node);
    void removeFromTail();
    void removeFromHead();
    ListNode* getNodeFromIndex(int i);
    void removeFromIndexes(int i, int j);
};
