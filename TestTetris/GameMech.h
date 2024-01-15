#pragma once
#ifndef TETRIS_GAMEMECH_H
#define TETRIS_GAMEMECH_H

//#include "MasterHeader.h"
#include "Clock.h"
#include "Tetromino.h"
//#include "Board.h"
//#include "Point.h"

enum class eKeys1 { LEFT = 'a', RIGHT = 's', ROTATE_CLOCKWISE = 's', ROTATE_COUNTERCLOCKWISE = 'w', DROP = 'x', ESC = 27 };
enum class eKeys2 { LEFT = 'j', RIGHT = 'l', ROTATE_CLOCKWISE = 'k', ROTATE_COUNTERCLOCKWISE = 'i', DROP = 'm', ESC = 27 };
class GameMech {
public:
    Board activeLines;
    //void updateScore(int i);
    Tetromino getNextTet();
    Tetromino currTet;
    //Tetromino nextTet;
    void drawBorder(int minx, int miny, bool isGameBorder);
    void init(Board* board);
    void runGame(Clock* clock, bool p1);
    void freeMemory();

    static constexpr int MIN_Y = 3;
    static constexpr int MIN_X = 10;
    static constexpr int MIN_X1 = 9;
    static constexpr int MIN_X2 = 55;
};
#endif //TETRIS_GAMEMECH_H
