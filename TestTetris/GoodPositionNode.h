#ifndef TETRIS_GOODPOSTIONNODE_H
#define TETRIS_GOODPOSTIONNODE_H

#include "GameMech.h"

class GoodPositionNode {
public:
	GoodPositionNode(const int headX, const int headY, const int position, const int coverage=0, const int blockedSpaces=0, const int bottomY=0, const int linesAdded=0, const int linesFilled = 0, const int emptyNeighbors = 0): coverage(coverage), headX(headX), headY(headY), position(position), blockedSpaces(blockedSpaces), bottomY(bottomY), linesAdded(linesAdded), linesFilled(linesFilled), neighbors(emptyNeighbors){
		next = nullptr;
		prev = nullptr;
	}

	int headX;
	int headY;
	int bottomY;
	short position;
	int coverage;
	int blockedSpaces;
	int linesAdded;
	int linesFilled;
	int neighbors;

	bool betterThen(GoodPositionNode* node);

	GoodPositionNode* next;
	GoodPositionNode* prev;
};

#endif // TETRIS_GOODPOSTIONNODE_H
