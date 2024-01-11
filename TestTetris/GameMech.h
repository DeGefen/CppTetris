#pragma once
#ifndef TETRIS_GAMEMECH_H
#define TETRIS_GAMEMECH_H

#include "MasterHeader.h"
#include "Tetromino.h"
#include "Board.h"

class GameMech {
public:
    Board* activeLines;
    unsigned int score = 0;
    void updateScore(int i);
    void getNextTet();
    Tetromino* currTet;
    Tetromino* nextTet;
    void drawBorder();
    void init(int num);
    void run();
    void freeMemory();
};
#endif //TETRIS_GAMEMECH_H
