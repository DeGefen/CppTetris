#include "GameMech.h"

bool GameMech::run(bool isDropped) { //returns false if player lost
	if (foundBomb) {
		board.checkFilled();
		foundBomb = false;
	}
	if (!curr.move(board) || isDropped) {
		foundBomb = board.checkFilled();
		next.erase();
		curr = next;
		bool isBomb = !(rand() % 20);
		int nextTetType = isBomb ? 7 : rand() % 7;
		next = Tetromino(nextTetType, game, color_mod);
		curr.jumpTo(GameConfig::STARTING_X, GameConfig::STARTING_Y);
		curr.draw();
		next.jumpTo(GameConfig::NEXT_X, GameConfig::NEXT_Y);
		next.draw();
	}
	if (board.count() > GameConfig::GAME_HEIGHT) return false;
	return true;
}

void GameMech::lunch() {
	foundBomb = false;
	next = Tetromino(rand() % 7, game, color_mod);
	curr = Tetromino(rand() % 7, game, color_mod);
	curr.jumpTo(GameConfig::STARTING_X, GameConfig::STARTING_Y);
	next.jumpTo(GameConfig::NEXT_X, GameConfig::NEXT_Y);
	board = Board(game, color_mod);
}
