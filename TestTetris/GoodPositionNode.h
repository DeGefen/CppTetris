#ifndef TETRIS_GOODPOSTIONNODE_H
#define TETRIS_GOODPOSTIONNODE_H

#include "GameMech.h"

class GoodPositionNode {
public:
	GoodPositionNode(const int coverage, const int headX, const int headY, const int position, const int blockedSpaces, const int bottomY): coverage(coverage), headX(headX), headY(headY), position(position), blockedSpaces(blockedSpaces), bottomY(bottomY) {
		next = nullptr;
		prev = nullptr;
	}
	~GoodPositionNode() { delete[] this; }
	int headX;
	int headY;
	int bottomY;
	short position;
	int coverage;
	int blockedSpaces;

	bool betterThen(GoodPositionNode* node);

	GoodPositionNode* next;
	GoodPositionNode* prev;
};

#endif // TETRIS_GOODPOSTIONNODE_H
