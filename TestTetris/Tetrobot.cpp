#include "Tetrobot.h"

/*MovesList TetroBot::getMovesList(Board& board, GoodPositionNode* goodPos, Tetromino& upTet) {
	int heightDiff = goodPos->headY - upTet.getHeadY();
	int sideDiff = upTet.getHeadX() - goodPos->headX;
	Tetromino downTet = getTetFromPos(goodPos, upTet);
	int linesToCheckCount = board.count() - goodPos->headY;
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
		}
		while (!canMoveUp) {
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
} */

bool TetroBot::getMovesList(GameMech& game, GoodPositionNode* goodPos) {
	Tetromino &tetro = game.curr;
	int heightDiff = goodPos->headY - tetro.getHeadY();
	int sideDiff = tetro.getHeadX() - goodPos->headX;
	int linesToCheckCount = game.board.count() - goodPos->headY;
	std::vector<GoodPositionNode> checkPoint;
	int lastCheckPoint = 0;
	setTetToPos(goodPos, tetro);
	bool topBlocked = false;
	bool leftBlocked = false;
	bool rightBlocked = false;
	int attempts = 0;

	movesList.addMove(MovesNode::moves::DROP);

	while (GameConfig::STARTING_Y + 1 < tetro.getHeadY()) {
		tetro.jumpTo(tetro.getHeadX(), tetro.getHeadY() - 1);
		if (tetro.checkTetroMove(game.board)) {
			if (!topBlocked) {
				movesList.addMove(MovesNode::moves::DOWN);
				GoodPositionNode node(tetro.getHeadX(), tetro.getHeadY() + 1, tetro.position);
				checkPoint.push_back(node);
				lastCheckPoint = 1;
				leftBlocked = false;
				continue;
			}
		}
		else topBlocked = false;
		tetro.jumpTo(tetro.getHeadX(), tetro.getHeadY() + 1);
		if (!leftBlocked) {
			tetro.jumpTo(tetro.getHeadX()-1, tetro.getHeadY());
			if (tetro.checkTetroMove(game.board)) {
				movesList.addMove(MovesNode::moves::RIGHT);
				lastCheckPoint++;
				continue;
			}
			tetro.jumpTo(tetro.getHeadX() + 1, tetro.getHeadY());
			leftBlocked = true;
		}
		if (!rightBlocked) {
			tetro.jumpTo(tetro.getHeadX() + 1, tetro.getHeadY());
			if (tetro.checkTetroMove(game.board)) {
				movesList.addMove(MovesNode::moves::LEFT);
				lastCheckPoint++;
				continue;
			}
			tetro.jumpTo(tetro.getHeadX() - 1, tetro.getHeadY());
			rightBlocked = true;
		}
		if (!checkPoint.empty()) {
			GoodPositionNode node = checkPoint.back();
			setTetToPos(&node, tetro);
			checkPoint.pop_back();
			for (; lastCheckPoint > 0; lastCheckPoint--) {
				movesList.popHead();
			}
		}
		attempts++;
		if (attempts == 10) return false;
		topBlocked = true;
		leftBlocked = false;
		rightBlocked = false;
	}

	while (GameConfig::STARTING_X < tetro.getHeadX()) {
		tetro.jumpTo(tetro.getHeadX() - 1, tetro.getHeadY());
		movesList.addMove(MovesNode::moves::RIGHT);
	}
	while (GameConfig::STARTING_X > tetro.getHeadX()) {
		tetro.jumpTo(tetro.getHeadX() + 1, tetro.getHeadY());
		movesList.addMove(MovesNode::moves::LEFT);
	}
	while (0 != tetro.position) {
		tetro.rotate(game.board, 1, false);
		movesList.addMove(MovesNode::moves::ROTATE_CLOCKWISE);
	}

	movesList.addMove(MovesNode::moves::DOWN);
	tetro.jumpTo(tetro.getHeadX(), tetro.getHeadY() - 1);
	return true;
}


void TetroBot::setTetToPos(GoodPositionNode* pos, Tetromino &tetro) {
	tetro.jumpTo(pos->headX, pos->headY);
	tetro.position = pos->position;
}

int TetroBot::nextMove(GameMech& game) {//TODO: add bot level
	int keyMove = 0;
	bool miss = false;
	if (game.curr.getHeadX() == GameConfig::STARTING_X && game.curr.getHeadY() == GameConfig::STARTING_Y) {
		++moves_count;
		switch (level) {
		case 'c':
			if (moves_count == 10 + (rand() % 6 - 3)) {
				miss = true;
				moves_count = 0;
			}
			break;
		case 'b':
			if (moves_count == 40 + (rand() % 10 - 5)) {
				miss = true;
				moves_count = 0;
			}
		}
		movesList.empty();
		GoodPosition goodPositions(game, level);
		while (!getMovesList(game, goodPositions.getGoodPosition(miss))) {
			goodPositions.removeFromHead();
		}
	}
	MovesNode::moves move = movesList.popHead();
	switch (MovesNode::moves(move)) {
	case MovesNode::moves::LEFT:
		keyMove = !isGame1 ? (int)GameConfig::eKeys2::LEFT : (int)GameConfig::eKeys1::LEFT;
		break;
	case MovesNode::moves::RIGHT:
		keyMove = !isGame1 ? (int)GameConfig::eKeys2::RIGHT : (int)GameConfig::eKeys1::RIGHT;
		break;
	case MovesNode::moves::ROTATE_CLOCKWISE:
		keyMove = !isGame1 ? (int)GameConfig::eKeys2::ROTATE_CLOCKWISE : (int)GameConfig::eKeys1::ROTATE_CLOCKWISE;
		break;
	case MovesNode::moves::ROTATE_COUNTERCLOCKWISE:
		keyMove = !isGame1 ? (int)GameConfig::eKeys2::ROTATE_COUNTERCLOCKWISE : (int)GameConfig::eKeys1::ROTATE_COUNTERCLOCKWISE;
		break;
	case MovesNode::moves::DROP:
		keyMove = !isGame1 ? (int)GameConfig::eKeys2::DROP : (int)GameConfig::eKeys1::DROP;
	default:
		break;
	}
	return keyMove;
}
