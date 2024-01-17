#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "point.h"
#include "Board.h"
#include "general.h"
using namespace std;

#define GAME_HEIGHT 18
#define GAME_WIDTH 12
#define NUM_OF_CORDS 4
#define NULL_VALUE -1

class Tetromino {
public:
    Tetromino(int i = 0, bool b = true) { game = b; setTetro(i); position = 0; }
    Tetromino& operator=(const Tetromino& tetro) {
        if (&tetro != this) {
            p = tetro.p;
            game = tetro.game;
            cordX = tetro.cordX;
            cordY = tetro.cordY;
            type = tetro.type;
            position = 0;
            numOfPositions = tetro.numOfPositions;
        }
        return *this;
    }
    void jumpTo(int x, int y);
    void rotate(Board& board, short direction);
    void sideMove(Board& board, short direction);
    void dropDown(Board& board);
    bool move(Board& board);
    void draw();
    void erase();

private:
    int headX;
    int headY;
    vector<int> cordX;
    vector<int> cordY;
    char type;
    short position = 0;
    short numOfPositions;
    Point p;
    bool game;

    void setTetro(int num);
    Line* convertToLine(int y);
    bool checkTetroMove(Board& board);
    bool checkTetroMoveAUX(Board& board, int y);
    ListNode* placeTetro(Board& board, Line* tetroLine, int y);
};

#endif //TETRIS_TETROMINO_H
