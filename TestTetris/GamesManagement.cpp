#include "GamesManagement.h"

void GamesManagement::drawBorders(char color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    gotoxy(Point::MIN_X1-1, Point::MIN_Y - 2);
    cout << "Player1:          Next Shape: ";

    if (twoGames) { 
        gotoxy(Point::MIN_X2-1, Point::MIN_Y - 2);
        cout << "Player2:          Next Shape: ";
    }
	drawBordersAUX(Point::MIN_X1, Point::MIN_Y, _GAME_BORDER, color);
    drawBordersAUX(Point::MIN_X1 + 6 + GAME_WIDTH, Point::MIN_Y, _NEXT_TETRO_BORDER, color);
    if (twoGames) {
        drawBordersAUX(Point::MIN_X2, Point::MIN_Y, _GAME_BORDER, color);
        drawBordersAUX(Point::MIN_X2 + 6 + GAME_WIDTH, Point::MIN_Y, _NEXT_TETRO_BORDER,color);
    }
};

void GamesManagement::drawBordersAUX(int minx, int miny, bool isGameBorder, char color) {
    int width = isGameBorder ? GAME_WIDTH : NEXT_TET_WIDTH;
    int height = isGameBorder ? GAME_HEIGHT : NEXT_TET_HEIGHT;
    int backcolor = getColor(color);
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

void GamesManagement::FlashBoarder() {

}

void GamesManagement::runGames(bool& continueGame, bool& twoPlayerMode, bool& colorsMode, bool& exit) {
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
                continueGame = menuControl(twoPlayerMode, colorsMode, exit);
                if (exit) return;
                if (continueGame) {
                    game1.curr.draw();
                    game1.next.draw();
                    game1.board.draw();
                    game1.board.updateScore(0);
                    if (twoGames) {
                        game2.next.draw();
                        game2.next.draw();
                        game2.board.draw();
                        game2.board.updateScore(0);
                    }
                    drawBorders();
                }
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
    continueGame = true;
    endGame();
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
    if (twoGames && !dropped2) {
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

void GamesManagement::endGame() {
    if (!twoGames) {
        winner(3);
        return;
    }
    if (!game1_alive && !game2_alive){
        if (game1.board.score > game2.board.score)
            winner(1);
        else if (game1.board.score < game2.board.score)
            winner(2);
        else winner(3);
        return;
    }
    if (!game1_alive) winner(2);
    if (!game2_alive) winner(1);
}

void GamesManagement::winner(int n) {
    setColor(getColor(COLOR_TEXT));
    system("cls");
    std::cout << "\n\n\n\n\n                                    tetrip :(" << std::endl;
    Sleep(1000);
    system("cls");
    std::cout << "\n\n\n                    -----------------Winner----------------" << std::endl;
    std::cout << "\n";
    switch (n) {
    case 1:
        std::cout << "                      /////////////             /////      " << std::endl;
        std::cout << "                      ############///         //####//     " << std::endl;
        std::cout << "                      ###############//    ///######//     " << std::endl;
        std::cout << "                      ####//     ####//    #########//     " << std::endl;
        std::cout << "                      ####///////####//         ####//     " << std::endl;
        std::cout << "                      ##############//          ####//     " << std::endl;
        std::cout << "                      ###########/              ####//     " << std::endl;
        std::cout << "                      ####//                    ####//     " << std::endl;
        std::cout << "                      ####//               /////####////// " << std::endl;
        std::cout << "                      ####//               ##############//" << std::endl;
        std::cout << "                      ####/                ##############/ " << std::endl;
        break;
    case 2:
        std::cout << "                      /////////////          ///////////    " << std::endl;
        std::cout << "                      ############///      //##########//   " << std::endl;
        std::cout << "                      ###############//  //##############// " << std::endl;
        std::cout << "                      ####//     ####//  #####//     #####//" << std::endl;
        std::cout << "                      ####///////####//  ####/      /####// " << std::endl;
        std::cout << "                      ##############//           ///####//  " << std::endl;
        std::cout << "                      ###########/            ///####//     " << std::endl;
        std::cout << "                      ####//               ///####//        " << std::endl;
        std::cout << "                      ####//             //####//////////// " << std::endl;
        std::cout << "                      ####//             #################//" << std::endl;
        std::cout << "                      ####/              #################/ " << std::endl;
        break;
    case 3:
        std::cout << "\n\n\n                                    nobody...\n\n" << std::endl;
        break;
    }
    std::cout << "\n";
    std::cout << "                    -----------------Winner----------------\n\n\n\n\n\n\n" << std::endl;
    Sleep(500);
    std::cout << "      press any key to return to menu ";
    char choice = _getch();
 system("cls");
}
