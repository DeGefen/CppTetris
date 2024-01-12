#pragma once
#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

/*
I = #   O = ##   T =  #    J =  #   L = #    S =  ##   Z = ##
    #       ##       ###        #       #       ##          ##
    #                          ##       ##
    #
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include "point.h"
#include "Board.h"
using namespace std;

#define GAME_HEIGHT 18
#define GAME_WIDTH 12
#define STARTING_X_POSITION 5
#define STARTING_Y_POSITION 19
#define SPACE ' '
#define NUM_OF_CORDS 3

class Tetromino {
public:
    void rotate(Board& board, short direction);
    void moveTetro(Board& board, short direction);
    void dropTetro(Board& board);
    bool placeTetro(Board& board);
    void moveDown(Board& board);
    void move();
    void erase();

protected:

    int headX;
    int headY;
    vector<int> cordX;
    vector<int> cordY;
    short color;
    short position = 0;
    short numOfPositions;

    Line* convertToLine(int y);
    bool checkTetroMove(Board& board);
    bool checkTetroMoveAUX(Board& board, int y);
    void placeTetroAux(Board& board, Line* tetroLine, int y);
};

class tetro_I : public Tetromino {
    tetro_I() {
        cordX = { 0,0,0,-1,1,2 };
        cordY = { 1,-1,-2,0,0,0 };
        numOfPositions = 2;
        color = 0xBB;
    }
};

class tetro_O : Tetromino {
    tetro_O() {
        cordX = { 1,0,1 };
        cordY = { 0,-1,-1 };
        numOfPositions = 1;
        color = 0xEE;
    }
};

class tetro_T : Tetromino {
    tetro_T() {
        cordX = { 0, -1, 1, 0, -1, 0, -1, 1, 0, 0, 0, 1 };
        cordY = { 1, 0, 0, 1, 0, -1, 0, 0, -1, 1, -1, 0 };
        numOfPositions = 4;
        color = 0x55;
    }
};

class tetro_J : Tetromino {
    tetro_J() {
        cordX = { 0, 0, -1, -1, 1, 1, 0, 0, 1, 1, -1, -1 };
        cordY = { 1, -1, -1, 0, 0, -1, -1, 1, 1, 0, 0, 1 };
        numOfPositions = 4;
        color = 0x11;
    }
};

class tetro_L : Tetromino {
    tetro_L() {
        cordX = { 0, 0, 1, -1, 1, 1, 0, 0, -1, 1, -1, -1 };
        cordY = { 1, -1, -1, 0, 0, 1, -1, 1, 1, 0, 0, -1 };
        numOfPositions = 4;
        color = 0x66;
    }
};

class tetro_S : Tetromino {
    tetro_S() {
        cordX = { 1, 0, -1, 0, 1, 1 };
        cordY = { 0, -1, -1, 1, 0, -1 };
        numOfPositions = 2;
        color = 0xAA;
    }
};

class tetro_Z : Tetromino {
    tetro_Z() {
        cordX = { -1, 0, 1, 0, -1, -1 };
        cordY = { 0, -1, -1, 1, 0, -1 };
        numOfPositions = 2;
        color = 0x44;
    }
};

#endif //TETRIS_TETROMINO_H
