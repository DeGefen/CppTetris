#pragma once
#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

/*
I = #   O = ##   T =  #    J =  #   L = #    S =  ##   Z = ##
    #       ##       ###        #       #       ##          ##
    #                          ##       ##
    #
 */

#include "MasterHeader.h"
#include "Board.h"

class Tetromino {
public:
    void rotate(Board& board, short direction);
    void moveTetro(Board& board, short direction);
    void dropTetro(Board& board);
    bool placeTetro(Board& board);
    void moveDown(Board& board);
    void init(int headX, int headY, char type);

protected:
    int headX = STARTING_X_POSITION;
    int headY = STARTING_Y_POSITION;
    vector<int> cordX;
    vector<int> cordY;
    char type;
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
        type = 'I';
    }
};

class tetro_O : Tetromino {
    tetro_O() {
        cordX = { 1,0,1 };
        cordY = { 0,-1,-1 };
        numOfPositions = 1;
        type = 'O';
    }
};

class tetro_T : Tetromino {
    tetro_T() {
        cordX = { 0, -1, 1, 0, -1, 0, -1, 1, 0, 0, 0, 1 };
        cordY = { 1, 0, 0, 1, 0, -1, 0, 0, -1, 1, -1, 0 };
        numOfPositions = 4;
        type = 'T';
    }
};

class tetro_J : Tetromino {
    tetro_J() {
        cordX = { 0, 0, -1, -1, 1, 1, 0, 0, 1, 1, -1, -1 };
        cordY = { 1, -1, -1, 0, 0, -1, -1, 1, 1, 0, 0, 1 };
        numOfPositions = 4;
        type = 'J';
    }
};

class tetro_L : Tetromino {
    tetro_L() {
        cordX = { 0, 0, 1, -1, 1, 1, 0, 0, -1, 1, -1, -1 };
        cordY = { 1, -1, -1, 0, 0, 1, -1, 1, 1, 0, 0, -1 };
        numOfPositions = 4;
        type = 'L';
    }
};

class tetro_S : Tetromino {
    tetro_S() {
        cordX = { 1, 0, -1, 0, 1, 1 };
        cordY = { 0, -1, -1, 1, 0, -1 };
        numOfPositions = 2;
        type = 'S';
    }
};

class tetro_Z : Tetromino {
    tetro_Z() {
        cordX = { -1, 0, 1, 0, -1, -1 };
        cordY = { 0, -1, -1, 1, 0, -1 };
        numOfPositions = 2;
        type = 'Z';
    }
};

#endif //TETRIS_TETROMINO_H
