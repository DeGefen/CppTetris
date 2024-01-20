#ifndef TETRIS_LINE_H
#define TETRIS_LINE_H

#include <iostream>
#include <string>
using namespace std;

#define GAME_HEIGHT 18
#define GAME_WIDTH 12
#define NEXT_TET_HEIGHT 8
#define NEXT_TET_WIDTH 8
#define SPACE ' '
#define EMPTY_LINE "            "


class Line {
public:
    string arr = EMPTY_LINE;
    unsigned short countFilled;
    void setNewLine();
    void printLine();
    bool canIntersectLines(Line* line2, bool makeChange = true);
};

#endif //TETRIS_LINE_H
