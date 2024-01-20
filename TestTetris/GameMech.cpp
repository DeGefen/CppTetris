#include "GameMech.h"

bool GameMech::run(bool isDropped) { //return false if player lost
	if (isDropped || !curr.move(board)) {
		next.erase();
		curr = next;
		next = Tetromino(rand() % 7, game);
		curr.jumpTo(STARTING_X, STARTING_Y);
		curr.draw();
		next.jumpTo(NEXT_X, NEXT_Y);
		next.draw();
	}
	board.draw();
	if (board.count() >= GAME_HEIGHT)	return false;
	return true;
}

void GameMech::lunch() {
	next = Tetromino(rand() % 7, game);
	curr = Tetromino(rand() % 7, game);
	curr.jumpTo(STARTING_X, STARTING_Y);
	next.jumpTo(NEXT_X, NEXT_Y);
	board = Board(game);
}
