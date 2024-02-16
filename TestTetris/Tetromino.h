#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include "point.h"
#include "Board.h"
#include "general.h"


class Tetromino {
public:

    enum class tetromino_shape {I,O,T,J,L,S,Z,BOMB};

    static constexpr int _LEFT = -1;
    static constexpr int _RIGHT = 1;
    static constexpr int _ROTATE_CLOCKWISE = -1;
    static constexpr int _ROTATE_COUNTERCLOCKWISE = 1;

    Tetromino(int i = 0, bool game = true, bool* color_mod = nullptr) {setTetro(i); position = 0; p = Point(game ,color_mod); }
    Tetromino& operator=(const Tetromino& tetro) {
        p = tetro.p;
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
    int getCoverage(int& heady) const;
    bool checkTetroMove(Board& board);
    int getBlockedSpaces(Board& board,int x, int y) ;
    int getHeadX() const;
    int getHeadY() const;
    char getType() const;
    int getHight() const;
    int getPotential(ListNode* node) const;
    int getNeighbors(Board& board, int x, int y) const;

    short position = 0;
    short numOfPositions;

private:
    int headX;
    int headY;    
    int cordX[16];
    int cordY[16];
    char type;
    Point p;

    void copyCords(int* arr1,const int* arr2);
    void setTetro(int num);
    Line* convertToLine(int y);
    bool checkTetroMoveAUX(Board& board, int y);
    void placeTetro(Board& board, Line* tetroLine, int y);
    void plantBomb(Board& board);
};

#endif //TETRIS_TETROMINO_H
