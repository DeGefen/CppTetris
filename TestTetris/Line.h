#ifndef TETRIS_LINE_H
#define TETRIS_LINE_H

#include "GameConfig.h"
#include <iostream>

class Line {
public:
    char arr[13] = "            ";
    unsigned short countFilled;
    void setNewLine();
    void printLine();
    bool canIntersectLines(Line* line2, bool makeChange = true);
    void bombLine(int fromX, int toX);
    //void bombLine(int fromX, int toX);
};

#endif //TETRIS_LINE_H
