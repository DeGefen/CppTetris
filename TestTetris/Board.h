#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include "ListNode.h"
#include "Point.h"
#include <Windows.h>
#include "general.h"

class Board {
public:
    Board(bool game = true) {
        head = nullptr;
        tail = nullptr;
        nodesCount = 0;
        score = 0;
        p = Point(game);
        isGame1 = game; }

    unsigned int score = 0;

    ListNode* getTail() const;
    ListNode* getHead() const;
    void updateScore(int i);
    void addToHead(ListNode* node);
    void addToTail(ListNode* node);
    void remove(ListNode** node);
    ListNode* getNodeFromIndex(int i);
    int count() const;
    void draw(int from = 0);
    void erase();
  
  void blowBomb(int coordX, int coordY);

private:
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    Point p;
    bool isGame1;
    int nodesCount;

    void removeFromTail();
    void removeFromHead();
    void removeFromMiddle(ListNode* node);

    void drawScore(int minx, int miny);
    void eraseLine(int y);


};

#endif