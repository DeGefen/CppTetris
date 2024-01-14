//
// Created by Eylon Serok on 07/01/2024.
//

#include "GamesManagement.h"

#include <Windows.h>

const int GamesManagement::COLORS[] = { FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, 96, 176, 224, 95, 23, 111, 143, 48 };
const int GamesManagement::NUM_OF_COLORS = sizeof(COLORS) / sizeof(int);

void GamesManagement::drawBorders()
{
	cout << "Player 1:	Next Shape:	   Player2:	Next Shape:";
	game1->drawBorder(1, 2, true);
	game1->drawBorder(GAME_WIDTH + 6, 2, false);
	game2->drawBorder(3 * GAME_WIDTH, 2, true);
	game1->drawBorder(4*GAME_WIDTH + 6, 2, false);
};
