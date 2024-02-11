#include "Tetrobot.h"

MovesList TetroBot::getMovesList(Board& board, GoodPositionNode* goodPos, Tetromino* upTet) {
	int heightDiff = goodPos->headY - upTet->getHeadY();
	int sideDiff = upTet->getHeadX() - goodPos->headX;
	Tetromino downTet = getTetFromPos(goodPos, upTet);
	//int linesToCheckCount = board.count() - goodPos->headY;
	bool MoveRight, canMoveSidways;
	int xSaver;
	MovesList movesList;

	for (int i = 0; i < heightDiff; i++) {
		downTet.jumpTo(downTet.getHeadY() - 1, downTet.getHeadX());
		bool canMoveUp = downTet.checkTetroMove(board);
		if (!canMoveUp) {
			//downTet.jumpTo(downTet.getHeadY() - 1, downTet.getHeadX());
			xSaver = downTet.getHeadX();
			canMoveSidways = false;
			MoveRight = true;
		} while (!canMoveUp) {
			downTet.jumpTo(downTet.getHeadY(), downTet.getHeadX() + MoveRight * 1);
			canMoveSidways = downTet.checkTetroMove(board);
			if (!canMoveSidways) {
				downTet.jumpTo(downTet.getHeadY(), xSaver);
				MoveRight = false;
			}
			downTet.jumpTo(downTet.getHeadY() - 1, downTet.getHeadX());
			canMoveUp = downTet.checkTetroMove(board);
			if (!canMoveUp)
				downTet.jumpTo(downTet.getHeadY() + 1, downTet.getHeadX());
			else for (int j = 0; j < abs(downTet.getHeadX() - xSaver); j++) {
				movesList.addMove(moves(MoveRight * 1));
			}
		}
		movesList.addMove(moves(2));
	}
	for (int i = 0; i < goodPos->position; i++) {
		movesList.addMove(moves(5)); //TODO : check if right direction
	}
		
	return MovesList();
}

Tetromino TetroBot::getTetFromPos(GoodPositionNode* pos, Tetromino* tetro) {
	char type = tetro->getType();
	Tetromino &tet = *tetro;
	tet.jumpTo(pos->headX, pos->headY);
	tet.position = pos->position;
	return tet;
}
