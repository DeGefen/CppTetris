#ifndef TETRIS_GAMEMECH_H
#define TETRIS_GAMEMECH_H

#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include <conio.h>
#include "general.h"
#include "Clock.h"
#include "Tetromino.h"


class GameMech {
    bool game;
public:
    GameMech(bool b = true) { game = b; lunch(); }

    Board board;
    Tetromino next;
    Tetromino curr;
    bool run(bool isDropped);
    void lunch();

    static constexpr int STARTING_X = 5;
    static constexpr int STARTING_Y = -1;
    static constexpr int NEXT_X = 21;
    static constexpr int NEXT_Y = 3;
};
#endif //TETRIS_GAMEMECH_H
