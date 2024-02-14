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
    bool foundBomb;
public:
    GameMech(bool b = true) { game = b; lunch(); }

    Board board;
    Tetromino next;
    Tetromino curr;
    bool run(bool isDropped);
    void lunch();

};
#endif //TETRIS_GAMEMECH_H
