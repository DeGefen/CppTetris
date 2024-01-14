#pragma once
//
// Created by Eylon Serok on 07/01/2024.
//

#include "ListNode.h"

#ifndef TETRIS_Board_H
#define TETRIS_Board_H

#endif //TETRIS_Board_H

class Board {
    ListNode* head;
    ListNode* tail;
    int nodesCount;
    unsigned int score = 0;
    void updateScore(int i);
public:
    Board() { head = nullptr; tail = nullptr; nodesCount = 0; };
    void addToHead(ListNode* node);
    void addToTail(ListNode* node);
    void removeFromTail();
    void removeFromHead();
    ListNode* getNodeFromIndex(int i);
    void removeFromIndexes(int i, int j);
    int count() const;
    void draw();
};
