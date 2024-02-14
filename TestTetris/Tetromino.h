#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include "point.h"
#include "Board.h"
#include "general.h"


class Tetromino {
public:


    static constexpr int _LEFT = -1;
    static constexpr int _RIGHT = 1;
    static constexpr int _ROTATE_CLOCKWISE = -1;
    static constexpr int _ROTATE_COUNTERCLOCKWISE = 1;

    Tetromino(int i = 0, bool b = true) { game = b; setTetro(i); position = 0; }
    Tetromino& operator=(const Tetromino& tetro) {
        game = tetro.game;
        setTetro(tetro.type);
        position = 0;
        return *this;
    }
    void jumpTo(int x, int y);
    void rotate(Board& board, short direction, bool change = true);
    bool sideMove(Board& board, short direction, bool change = true);
    void dropDown(Board& board);
    bool move(Board& board, bool drawMod = true);
    void draw();
    void erase();
    int getCoverage(int& heady);
    bool checkTetroMove(Board& board);
    int getBlockedSpaces(Board& board,int x, int y);
    int getMinX() const;
    int getMaxX() const;
    int getHeadX() const;
    int getHeadY() const;
    char getType() const;
    int getHight() const;
    int getPotential(ListNode* node);
    int getNeighbors(Board& board, int x, int y);

    short position = 0;
    short numOfPositions;

private:
    int headX;
    int headY;    
    int cordX[16];
    int cordY[16];
    char type;
    Point p;
    bool game;

    void copyCords(int* arr1,const int* arr2);
    void setTetro(int num);
    Line* convertToLine(int y);
    bool checkTetroMoveAUX(Board& board, int y);
    void placeTetro(Board& board, Line* tetroLine, int y);
    void plantBomb(Board& board);
};

#endif //TETRIS_TETROMINO_H
