#include "GamesManagement.h"

void GamesManagement::start() {
    srand(time(0));
    //menu.loading_screen();
    bool continueGame;
    color_mod = new bool;
    *color_mod = true;
    exit = false;
    bot_level = 'a';
    while (true) {
        continueGame = menu.menuControl(twoGames, exit, isBot1, isBot2, bot_level, !game1_alive, *color_mod);
        if (exit) return;
        if (!continueGame) lunch();
        runGames();
    }
    delete[] color_mod;
}

void GamesManagement::drawBorders(char color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    gotoxy(Point::MIN_X1-1, Point::MIN_Y - 2);
    std::cout << "Player1:          Next Shape: ";

    if (twoGames) { 
        gotoxy(Point::MIN_X2-1, Point::MIN_Y - 2);
        std::cout << "Player2:          Next Shape: ";
    }
	drawBordersAUX(Point::MIN_X1, Point::MIN_Y, _GAME_BORDER, color);
    drawBordersAUX(Point::MIN_X1 + 6 + GameConfig::GAME_WIDTH, Point::MIN_Y, _NEXT_TETRO_BORDER, color);
    if (twoGames) {
        drawBordersAUX(Point::MIN_X2, Point::MIN_Y, _GAME_BORDER, color);
        drawBordersAUX(Point::MIN_X2 + 6 + GameConfig::GAME_WIDTH, Point::MIN_Y, _NEXT_TETRO_BORDER,color);
    }
};

void GamesManagement::drawBordersAUX(int minx, int miny, bool isGameBorder, char color) {
    int width = isGameBorder ? GameConfig::GAME_WIDTH : GameConfig::NEXT_TET_WIDTH;
    int height = isGameBorder ? GameConfig::GAME_HEIGHT : GameConfig::NEXT_TET_HEIGHT;
    int backcolor = Point::getColor(color);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
    {
        for (int col = minx; col < width + minx; col++)
        {
            gotoxy(col, miny - 1);
            std::cout << "-";

            gotoxy(col, height + miny);
            std::cout << "-";
        }

        for (int row = miny - 1; row <= height + miny; row++)
        {
            gotoxy(minx - 1, row);
            std::cout << "|";

            gotoxy(width + minx, row);
            std::cout << "|";
        }
    }
}

void GamesManagement::runGames() {

    game1.curr.draw();
    game1.next.draw();
    game1.board.draw();
    game1.board.updateScore(Board::add_score::print_current);
    if (twoGames) {
        game2.next.draw();
        game2.next.draw();
        game2.board.draw();
        game2.board.updateScore(Board::add_score::print_current);
    }
    drawBorders();

    while (game1_alive &&  game2_alive) {
        int keyPressed = 0;
        if (!bot2_down && !dropped2 && isBot2) {
            int move = bot2.nextMove(game2);
            if (!move) bot2_down = true;
            else movment(move);
        }
        if (!bot1_down && !dropped1 && isBot1) {
            int move = bot1.nextMove(game1);
            if (!move) bot1_down = true;
            else movment(move);
        }
        if (_kbhit()) {
            keyPressed = _getch();
            if (keyPressed == (int)GameConfig::eKeys1::ESC) return;
            movment(keyPressed, bot_mod);
        }
        clock.addMiliSeconds(speed);
        if (++counter == _THRESHHOLD) {
            counter = 0;
            reachedThreshHold++;
            game1_alive = game1.run(dropped1);
            if (twoGames)
                game2_alive = game2.run(dropped2);
            dropped1 = dropped2 = false;
            bot1_down = false;
            bot2_down = false;
        }
        if (reachedThreshHold == _SPEED_UP && speed>=_MAX_SPEED) {
            --speed;
            reachedThreshHold = 0;
        }
    }
    endGame();
}

void GamesManagement::movment(int key, int mode) {
    if (mode < 2 && !dropped1) {
        switch (key) {
        case (int)GameConfig::eKeys1::LEFT:
        case (int)GameConfig::eKeys1::LEFT + GameConfig::CAPITAL:
            game1.curr.sideMove(game1.board, Tetromino::_LEFT);
            break;
        case (int)GameConfig::eKeys1::RIGHT:
        case (int)GameConfig::eKeys1::RIGHT + GameConfig::CAPITAL:
            game1.curr.sideMove(game1.board, Tetromino::_RIGHT);
            break;
        case (int)GameConfig::eKeys1::ROTATE_CLOCKWISE:
        case (int)GameConfig::eKeys1::ROTATE_CLOCKWISE + GameConfig::CAPITAL:
            game1.curr.rotate(game1.board, Tetromino::_ROTATE_CLOCKWISE);
            break;
        case (int)GameConfig::eKeys1::ROTATE_COUNTERCLOCKWISE:
        case (int)GameConfig::eKeys1::ROTATE_COUNTERCLOCKWISE + GameConfig::CAPITAL:
            game1.curr.rotate(game1.board, Tetromino::_ROTATE_COUNTERCLOCKWISE);
            break;
        case (int)GameConfig::eKeys1::DROP:
        case (int)GameConfig::eKeys1::DROP + GameConfig::CAPITAL:
            dropped1 = true;
            game1.curr.dropDown(game1.board);
            game1.board.draw();
            break;
        default:
            break;
        }
    }
    if (mode < 1 && twoGames && !dropped2) {
        switch (key) {
        case (int)GameConfig::eKeys2::LEFT:
        case (int)GameConfig::eKeys2::LEFT + GameConfig::CAPITAL:
            game2.curr.sideMove(game2.board, Tetromino::_LEFT);
            break;
        case (int)GameConfig::eKeys2::RIGHT:
        case (int)GameConfig::eKeys2::RIGHT + GameConfig::CAPITAL:
            game2.curr.sideMove(game2.board, Tetromino::_RIGHT);
            break;
        case (int)GameConfig::eKeys2::ROTATE_CLOCKWISE:
        case (int)GameConfig::eKeys2::ROTATE_CLOCKWISE + GameConfig::CAPITAL:
            game2.curr.rotate(game2.board, Tetromino::_ROTATE_CLOCKWISE);
            break;
        case (int)GameConfig::eKeys2::ROTATE_COUNTERCLOCKWISE:
        case (int)GameConfig::eKeys2::ROTATE_COUNTERCLOCKWISE + GameConfig::CAPITAL:
            game2.curr.rotate(game2.board, Tetromino::_ROTATE_COUNTERCLOCKWISE);
            break;
        case (int)GameConfig::eKeys2::DROP:
        case (int)GameConfig::eKeys2::DROP + GameConfig::CAPITAL:
            dropped2 = true;
            game2.curr.dropDown(game2.board);
            game2.board.draw();
            break;
        default:
            break;
        }
    }
}

void GamesManagement::lunch() {
    counter = 0; speed = _DEFAULT_SPEED; reachedThreshHold = 0;  bot_mod = 0;
    dropped1 = dropped2 = false;
    game1_alive = game2_alive = true;

    clock.reset();

    game1 = GameMech(GameConfig::IS_GAME1, color_mod);
    game1.curr.jumpTo(GameConfig::STARTING_X, GameConfig::STARTING_Y);
    game1.next.jumpTo(GameConfig::NEXT_X, GameConfig::NEXT_Y);
    if (twoGames) {
        game2 = GameMech(GameConfig::IS_GAME2, color_mod);
        game2.curr.jumpTo(GameConfig::STARTING_X, GameConfig::STARTING_Y);
        game2.next.jumpTo(GameConfig::NEXT_X, GameConfig::NEXT_Y);
    }

    if (isBot1) {
        bot1_down = false;
        bot1.setBot(GameConfig::IS_GAME1, bot_level);
        bot_mod++;
    }
    if (isBot2) {
        bot2_down = false;
        bot2.setBot(GameConfig::IS_GAME2, bot_level);
        bot_mod++;
    }

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
    menu.setColor(Point::getColor(GameConfig::COLOR_TEXT));
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
