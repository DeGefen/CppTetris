#pragma once
#ifndef TETRIS_LINE_H
#define TETRIS_LINE_H

#include <iostream>
#include <string>
using namespace std;

#define GAME_HEIGHT 18
#define GAME_WIDTH 12
#define SPACE ' '


class Line {
public:
    string arr;
    unsigned short countFilled = 0;
    void setNewLine();
    void printLine();
    bool canIntersectLines(Line* line2, bool makeChange = true);
};

#endif //TETRIS_LINE_H
