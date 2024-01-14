#pragma once
#ifndef TETRIS_GAMESMANAGEMENT_H
#define TETRIS_GAMESMANAGEMENT_H

//#include "Board.h"
#include "GameMech.h"
#include "Clock.h"

class GamesManagement {
    GameMech* game1;
    GameMech* game2;


    enum class eKeys1 { LEFT = 'a', RIGHT = 's', ROTATE_CLOCKWISE = 's', ROTATE_COUNTERCLOCKWISE = 'w', DROP = 'x', ESC = 27 };
    enum class eKeys2 { LEFT = 'j', RIGHT = 'l', ROTATE_CLOCKWISE = 'k', ROTATE_COUNTERCLOCKWISE = 'i', DROP = 'm', ESC = 27 };

public:
    //    static constexpr int GAME_WIDTH = 20;
    //    static constexpr int GAME_HEIGHT = 20;
    //
    static constexpr int MIN_Y = 3;
    static constexpr int MIN_X = 10;
    static constexpr int MIN_X1 = 9;
    static constexpr int MIN_X2 = 55;

    static const int COLORS[];
    static const int NUM_OF_COLORS;

    void drawBorders();

    //void gotoxy(int, int);
    //void clrscr();
};
#endif //TETRIS_GAMESMANAGEMENT_H
