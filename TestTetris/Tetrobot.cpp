#include "Tetrobot.h"

MovesList TetroBot::getMovesList(Board* board, GoodPositionNode* goodPos, Tetromino* upTet){
	Point tetHead = upTet->getHeadCoords();
	int heightDiff = tetHead.y - goodPos->headY;
	int sideDiff = tetHead.x - goodPos->headX;
	Tetromino downTet = getTetFromPos(goodPos, upTet);
	int linesToCheckCount = board->count() - goodPos->headY;
	//Line lineToCheck = createLineFromPos(goodPos);
	Line lineToCheck = (downTet).convertToLine(goodPos->headY);
	Line* lineAbove = board->getNodeFromIndex(goodPos->headY+1)->line;

	GoodPositionNode currPos = *goodPos;
	for (int i = 0; i < linesToCheckCount; i++) {

		bool canIntersect = lineToCheck.canIntersectLines(lineAbove, false);
		while (!canIntersect) {
			lineToCheck = createLineFromPos(&currPos, 1);
			canIntersect = lineToCheck.canIntersectLines(lineAbove, false);
		}
	}
	return MovesList();
}

Line TetroBot::createLineFromPos(GoodPositionNode* pos, int movesLeft) {
	return Line();
}

Tetromino TetroBot::getTetFromPos(GoodPositionNode* pos, Tetromino* tetro) {
	Tetromino tet = *tetro;
	tet.position = pos->position;
	return tet;
}
