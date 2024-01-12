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
#include <Windows.h>
#include "point.h"
#include "Board.h"
using namespace std;

#define GAME_HEIGHT 18
#define GAME_WIDTH 12
#define NUM_OF_CORDS 4
#define NULL_VALUE -1

class Tetromino {
public:
    void jumpTo(int x, int y);
    void rotate(Board& board, short direction);
    void sideMove(Board& board, short direction);
    void dropDown(Board& board);
    bool move(Board& board);
    void draw();
    void erase();
    void setTetro(int num);

private:
    int headX;
    int headY;
    vector<int> cordX;
    vector<int> cordY;
    char type;
    short color;
    short position = 0;
    short numOfPositions;

    Line* convertToLine(int y);
    bool checkTetroMove(Board& board);
    bool checkTetroMoveAUX(Board& board, int y);
    void placeTetroAux(Board& board, Line* tetroLine, int y);
};

#endif //TETRIS_TETROMINO_H
