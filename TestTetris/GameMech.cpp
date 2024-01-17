#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include <conio.h>
#include "general.h"
#include "GamesManagement.h"

void GameMech::run(bool isDropped) {
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
}

void GameMech::lunch() {
	next = Tetromino(rand() % 7, game);
	curr = Tetromino(rand() % 7, game);
	curr.jumpTo(STARTING_X, STARTING_Y);
	next.jumpTo(NEXT_X, NEXT_Y);
	board = Board(game);
}
