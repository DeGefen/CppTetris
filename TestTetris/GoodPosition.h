#ifndef TETRIS_GOODPOSTION_H
#define TETRIS_GOODPOSTION_H

#include "GameMech.h"
#include "GoodPositionNode.h"

class GoodPosition {



	GoodPositionNode* head;
	GoodPositionNode* tail;
	int nodesCount;
	char level;

	void findGoodPositions(GameMech& game);
	void bombPosition(GameMech& game);

	void addNode(int coverage, int headX, int headY, int position, int blockedSpaces, int bottomY, int linesAdded, int linesFilled, int emptyNeighbors);
	void addToHead(GoodPositionNode* node);
	void addToTail(GoodPositionNode* node);
	void addToPrev(GoodPositionNode* node, GoodPositionNode* newNode);

public:
	GoodPosition(GameMech& game, char level) :level(level) {
		head = nullptr;
		tail = nullptr;
		findGoodPositions(game);
	}

	void remove(GoodPositionNode* node);
	GoodPositionNode* getGoodPosition(bool miss) const;
};

#endif // TETRIS_GOODPOSTION_H