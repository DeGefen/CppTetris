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
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    Point p;
    bool isGame1 = true;
public:
    Board(bool game = true) { head = nullptr; tail = nullptr; nodesCount = 0; p = Point(game); }
    //Board& operator=(Board& tetro) {} need to inplment!!
    int nodesCount = 0;
    unsigned int score = 0;


    void updateScore(int i);
    void drawScore(int minx, int miny);
    void addToHead(ListNode* node);
    void addToTail(ListNode* node);
    void removeFromTail();
    void removeFromHead();
    void removeFromMiddle(ListNode* node);
    void remove(ListNode** node);
    ListNode* getNodeFromIndex(int i);
    int count() const;
    void draw(int from = 0);
    void erase();
    void eraseLine(int y);
    void init();
};