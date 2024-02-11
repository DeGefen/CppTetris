#ifndef TETRIS_TETROBOT_H
#define TETRIS_TETROBOT_H

#include "GoodPosition.h"
#include "MovesList.h"

class TetroBot {
	Tetromino getTetFromPos(GoodPositionNode* pos, Tetromino* tetro);
public:
	MovesList getMovesList(Board& board, GoodPositionNode* goodPos, Tetromino* tet);
};


#endif // TETRIS_TETROBOT_H