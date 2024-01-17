#include "GamesManagement.h"

void GamesManagement::drawBorders() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    gotoxy(0, 0);
    cout << "	Player 1:	  Next Shape:";
    if(twoGames) cout << "		      Player2:	        Next Shape : ";
	drawBordersAUX(Point::MIN_X1, 2, _GAME_BORDER);
    drawBordersAUX(Point::MIN_X1 + 6 + GAME_WIDTH, 2, _NEXT_TETRO_BORDER);
    if (twoGames) {
        drawBordersAUX(Point::MIN_X2, 2, _GAME_BORDER);
        drawBordersAUX(Point::MIN_X2 + 6 + GAME_WIDTH, 2, _NEXT_TETRO_BORDER);
    }
};

void GamesManagement::drawBordersAUX(int minx, int miny, bool isGameBorder) {
    int width = isGameBorder ? GAME_WIDTH : NEXT_TET_WIDTH;
    int height = isGameBorder ? GAME_HEIGHT : NEXT_TET_HEIGHT;
    int backcolor = getColor('G');
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
    {
        for (int col = minx; col < width + minx; col++)
        {
            gotoxy(col, miny - 1);
            cout << "-";

            gotoxy(col, height + miny);
            cout << "-";
        }

        for (int row = miny - 1; row <= height + miny; row++)
        {
            gotoxy(minx - 1, row);
            cout << "|";

            gotoxy(width + minx, row);
            cout << "|";
        }
    }
}

void GamesManagement::runGames(bool& continueGame, bool& twoPlayerMode, bool& colorsMode) {
    dropped1 = dropped2 = false;
    game1_alive = game2_alive = true;
    game1.next.jumpTo(GameMech::NEXT_X,GameMech::NEXT_Y);
    game1.next.draw();
    game1.board.updateScore(0);
    if (twoGames) { 
        game2.next.jumpTo(GameMech::NEXT_X, GameMech::NEXT_Y);
        game2.next.draw();
        game2.board.updateScore(0);
    }
    drawBorders();
    while (game1_alive && game2_alive) {
        int keyPressed = 0;
        if (_kbhit()) {
            keyPressed = _getch();
            if (keyPressed == (int)eKeys1::ESC) {
                continueGame = menuControl(twoPlayerMode, colorsMode);
                if (continueGame)
                    drawBorders();
                else
                    return;
            }
            movment(keyPressed);
        }
        clock.addMiliSeconds(50);
        if (++counter == threshHold) {
            counter = 0;
            reachedThreshHold++;
            game1_alive = game1.run(dropped1);
            if (twoGames)
                game2_alive = game2.run(dropped2);
            dropped1 = dropped2 = false;
        }
        if (reachedThreshHold == _SPEED_UP && threshHold>=_MAX_SPEED) {
            --threshHold;
            reachedThreshHold = 0;
        }
    }
    continueGame = false;
    endScreen();
}

void GamesManagement::movment(int key) {
    if (!dropped1) {
        switch (key) {
        case (int)eKeys1::LEFT:
        case (int)eKeys1::LEFT + CAPITAL:
            game1.curr.sideMove(game1.board, _LEFT);
            break;
        case (int)eKeys1::RIGHT:
        case (int)eKeys1::RIGHT + CAPITAL:
            game1.curr.sideMove(game1.board, _RIGHT);
            break;
        case (int)eKeys1::ROTATE_CLOCKWISE:
        case (int)eKeys1::ROTATE_CLOCKWISE + CAPITAL:
            game1.curr.rotate(game1.board, _ROTATE_CLOCKWISE);
            break;
        case (int)eKeys1::ROTATE_COUNTERCLOCKWISE:
        case (int)eKeys1::ROTATE_COUNTERCLOCKWISE + CAPITAL:
            game1.curr.rotate(game1.board, _ROTATE_COUNTERCLOCKWISE);
            break;
        case (int)eKeys1::DROP:
        case (int)eKeys1::DROP + CAPITAL:
            dropped1 = true;
            game1.curr.dropDown(game1.board);
            game1.board.draw();
            break;
        default:
            break;
        }
    }
    if (twoGames & !dropped2) {
        switch (key) {
        case (int)eKeys2::LEFT:
        case (int)eKeys2::LEFT + CAPITAL:
            game2.curr.sideMove(game2.board, _LEFT);
            break;
        case (int)eKeys2::RIGHT:
        case (int)eKeys2::RIGHT + CAPITAL:
            game2.curr.sideMove(game2.board, _RIGHT);
            break;
        case (int)eKeys2::ROTATE_CLOCKWISE:
        case (int)eKeys2::ROTATE_CLOCKWISE + CAPITAL:
            game2.curr.rotate(game2.board, _ROTATE_CLOCKWISE);
            break;
        case (int)eKeys2::ROTATE_COUNTERCLOCKWISE:
        case (int)eKeys2::ROTATE_COUNTERCLOCKWISE + CAPITAL:
            game2.curr.rotate(game2.board, _ROTATE_COUNTERCLOCKWISE);
            break;
        case (int)eKeys2::DROP:
        case (int)eKeys2::DROP + CAPITAL:
            dropped2 = true;
            game2.curr.dropDown(game2.board);
            game2.board.draw();
            break;
        default:
            break;
        }
    }
}

void GamesManagement::lunch(bool isTwoGames) {
    srand(time(0));
    counter = 0; threshHold = _DEFAULT_SPEED; reachedThreshHold = 0; twoGames = isTwoGames;
    game1 = GameMech(true);
    if (isTwoGames) game2 = GameMech(false);
}
