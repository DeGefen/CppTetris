#ifndef TETRIS_GOODPOSTION_H
#define TETRIS_GOODPOSTION_H

#include "GameMech.h"
#include "GoodPositionNode.h"

class GoodPosition {
	GoodPositionNode* head;
	GoodPositionNode* tail;
	int nodesCount;


	void addNode(int coverage, int headX, int headY, int position, int blockedSpaces, int bottomY);
	void findPlacement(GameMech& game); //WIP
	void findGoodPositions(GameMech& game);
	void addToHead(GoodPositionNode* node);
	void addToTail(GoodPositionNode* node);
	GoodPositionNode* getGoodPosition(bool randPosition = false);
};

#endif // TETRIS_GOODPOSTION_H