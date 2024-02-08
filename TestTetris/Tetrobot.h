#ifndef TETRIS_TETROBOT_H
#define TETRIS_TETROBOT_H

#include "GoodPosition.h"
#include "MovesList.h"

class TetroBot {
	MovesList getMovesList(Board* board, GoodPositionNode* goodPos, Tetromino* tet);
	Line createLineFromPos(GoodPositionNode* pos, int movesLeft=0);
	Tetromino getTetFromPos(GoodPositionNode* pos, Tetromino* tetro);
};


#endif // TETRIS_TETROBOT_H