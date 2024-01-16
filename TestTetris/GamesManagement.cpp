#include "GamesManagement.h"
#include <cstdlib>

void GamesManagement::drawBorders() {
	cout << "	Player 1:	  Next Shape:		      Player2:	        Next Shape:";
	game1->drawBorder(GameMech::MIN_X1, 2, true);
	game1->drawBorder(GameMech::MIN_X1 + 6 + GAME_WIDTH, 2, false);
	game2->drawBorder(GameMech::MIN_X2, 2, true);
	game1->drawBorder(GameMech::MIN_X2 + 6 + GAME_WIDTH, 2, false);
};

void GamesManagement::runGames() {
    menuControl();
    drawBorders();
	//game1->runGame(&clock, true);
	//game2->runGame(&clock, true);
    srand((time(0)));
    clock.addMiliSeconds(500);
    while (true) {
        int keyPressed = 0;
        if (_kbhit()) {
            keyPressed = _getch();
            if (keyPressed == (int)eKeys1::ESC)
                break;
        }
        Sleep(500);

    }


}

void movment(int key) {
    switch (key) {
    case (int)eKeys1::LEFT:
        break;
    default:
        break;
    }
}