#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include "ListNode.h"
#include "Point.h"
#include "general.h"

class Board {
public:
    enum class add_score { print_current, one_row, two_rows, three_rows, four_rows };

    Board(bool game = true, bool* color_mod = nullptr) {
        head = nullptr;
        tail = nullptr;
        nodesCount = 0;
        score = 0;
        p = Point(game, color_mod);
        isGame1 = game;
    }

    unsigned int score = 0;

    ListNode* getTail() const;
    ListNode* getHead() const;
    void updateScore(add_score i);
    void addToHead(ListNode* node);
    void addToTail(ListNode* node);
    void remove(ListNode* node);
    bool checkFilled();
    ListNode* getNodeFromIndex(int i) const;
    int count() const;
    void draw(int from = 0);
    void erase();
    int matchCords(std::vector<int>& cords, bool empty_mode = true) const;
    bool blowBomb(ListNode* node);
    int getBoom(int x, int y) const;


private:
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    Point p;
    bool isGame1;
    int nodesCount;

    void removeFromTail();
    void removeFromHead();
    void removeFromMiddle(ListNode* node);

    void drawScore(int minx, int miny) const;
    void eraseLine(int y);


};

#endif