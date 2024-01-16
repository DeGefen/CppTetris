#pragma once
#ifndef TETRIS_GAMEMECH_H
#define TETRIS_GAMEMECH_H

//#include "MasterHeader.h"
#include "Clock.h"
#include "Tetromino.h"
//#include "Board.h"
//#include "Point.h"


class GameMech {
public:
    Board board;
    Tetromino next;
    Tetromino curr;
    void drawBorder(int minx, int miny, bool isGameBorder);
    void init(Board* board);
    void runGame(Clock* clock, bool p1);
    void freeMemory();
    //void updateScore(int i);

    static constexpr int MIN_Y = 3;
    static constexpr int MIN_X = 10;
    static constexpr int MIN_X1 = 9;
    static constexpr int MIN_X2 = 55;
};
#endif //TETRIS_GAMEMECH_H
