#ifndef TETRIS_TETROBOT_H
#define TETRIS_TETROBOT_H

#include "GoodPosition.h"
#include "MovesList.h"
#include "general.h"

class TetroBot {
	MovesList movesList;
	bool isGame1;
	char level = 'a';
	int moves_count = 0;
	void setTetToPos(GoodPositionNode* pos, Tetromino &tetro);
	bool getMovesList(GameMech& game, GoodPositionNode* goodPos);
public:
	int nextMove(GameMech& game);
	void setBot(bool isGame1, char level) {
		this->isGame1 = isGame1;
		this->level = level;
		moves_count = 0;
		movesList.empty();
	}
};


#endif // TETRIS_TETROBOT_H