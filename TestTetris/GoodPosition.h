#ifndef TETRIS_GOODPOSTION_H
#define TETRIS_GOODPOSTION_H

#include "GameMech.h"
#include "GoodPositionNode.h"

class GoodPosition {
	GoodPositionNode* head;
	GoodPositionNode* tail;
	int nodesCount;


	void findGoodPositions(GameMech& game);
	
	void addNode(int coverage, int headX, int headY, int position, int blockedSpaces, int bottomY);
	void findPlacement(GameMech& game); //WIP
	void addToHead(GoodPositionNode* node);
	void addToTail(GoodPositionNode* node);
public:
	GoodPosition(GameMech& game) { findGoodPositions(game);}
	GoodPositionNode* getGoodPosition(bool randPosition = false);
};

#endif // TETRIS_GOODPOSTION_H