#pragma once
//
// Created by Eylon Serok on 07/01/2024.
//

#include "ListNode.h"
#include "Point.h"
#include <Windows.h>
#include "general.h"

#ifndef TETRIS_Board_H
#define TETRIS_Board_H

#endif //TETRIS_Board_H

class Board {
    ListNode* head= nullptr;
    ListNode* tail = nullptr;
    //int nodesCount = 0;
    //unsigned int score = 0;
   //void updateScore(int i);
public:
    int nodesCount = 0;
    unsigned int score = 0;
    void updateScore(int i);
    Board() { head = nullptr; tail = nullptr; nodesCount = 0; };
    void addToHead(ListNode* node);
    void addToTail(ListNode* node);
    void removeFromTail();
    void removeFromHead();
    void removeFromMiddle(ListNode* node);
    void remove(vector<ListNode*> arr);
    ListNode* getNodeFromIndex(int i);
    //void removeFromIndexes(int i, int j);
    int count() const;
    void draw(int from = 0);
    void eraseLine(int y);
    void init();
};
