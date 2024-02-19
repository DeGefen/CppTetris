#include "Menu.h"

void Menu::loading_screen() const {
    srand(time(0));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
	gotoxy(0, 4);
    std::cout << "/////////////  ///////////  /////////////  /////////////  /////  //////////// " << std::endl;
    std::cout << "############// ##########// ############// ############// ####// ###########//" << std::endl;
    std::cout << "############/  ##########/  ############/  ############// ####// ###########/ " << std::endl;
    std::cout << "    ####//     ####//           ####//     ####//  ####// ####// ####//       " << std::endl;
    std::cout << "    ####//     ####///////      ####//     ####////####/  ####// ####//////// " << std::endl;
    std::cout << "    ####//     ##########//     ####//     ########//     ####// ###########//" << std::endl;
    std::cout << "    ####//     ##########/      ####//     ########////// ####// ###########//" << std::endl;
    std::cout << "    ####//     ####//           ####//     ####//  ####// ####//        ####//" << std::endl;
    std::cout << "    ####//     ####///////      ####//     ####//  ####// ####// ///////####//" << std::endl;
    std::cout << "    ####//     ##########//     ####//     ####//  ####// ####// ###########//" << std::endl;
    std::cout << "    ####/      ##########/      ####/      ####/   ####/  ####/  ###########/ " << std::endl;
    
    gotoxy(0, 17);

    std::cout << "  ###########################################################################  " << std::endl;
    std::cout << "  #                                                                         #  " << std::endl;
    std::cout << "  ###########################################################################  " << std::endl;

    gotoxy(3, 18);
    for (int i = 0; i< 71; ++i) {
        Sleep(25+(rand()%100));
        std::cout << '|';
    }
    Sleep(1300);
    std::cout << '|';
    Sleep(500);
    std::cout << '|';
    Sleep(75);

    gotoxy(0, 26);
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    system("cls");
}


void Menu::setColor(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

void Menu::displayMenu(int selectedOption, char& bot_level, bool firstTime, bool color_mod){
    std::string menuOptionsNames[] = { "(0) Start a new game - Single Player", "(1) Start a new game - Human vs Human", "(2) Start a new game - Human vs Computer", "(3) Start a new game - Computer vs Computer", "(4) - Continue a paused game", "(6) - TetroBot level","(7) - COLORS", "(8) - INSTRUCTIONS", "(9) - EXIT" };
    std::string toggleNames[] = { "OFF", "ON"};
    std::string Levels[] = { "(a) BEST", "(b) GOOD", "(c) NOVICE" };
    system("cls");
    menuTitle(color_mod);

    for (int i = 0; i <= NUM_OF_MENU_ITEMS; ++i) {
            setColor(selectedOption == i ? 10 : 7); // 10 is green, 7 is default color
            if (i == 6) {
                std::cout << "                    " << menuOptionsNames[i] << ": " << toggleNames[color_mod] << "\n\n";
            }                                 
            else if (i == 5) {
                std::cout << "                    " << menuOptionsNames[i] << ": ";
                setColor(bot_level == 'a' ? 0x70 : 0x07);
                std::cout << " " << Levels[0] << " ";

                setColor(bot_level == 'b' ? 0x70 : 0x07);
                std::cout << " " << Levels[1] << " ";

                setColor(bot_level == 'c' ? 0x70 : 0x07);
                std::cout << " " << Levels[2] << " \n\n";
            }
            else if (i == 4 && firstTime) {       
            }                                    
            else {                               
                std::cout << "                    " << menuOptionsNames[i] << "\n\n";
            }
    }
    setColor(7); // Reset to default color
}

bool Menu::menuControl(bool& twoGames, bool& exit, bool& bot1, bool& bot2, char& bot_level, bool firstTime, bool& color_mod) {
    char choice;
    int selectedOption = 0;
    menuTitle(color_mod);
    setColor(0);

    do {
        displayMenu(selectedOption, bot_level, firstTime, color_mod);
        std::cout << " Use W, S and ENTER to navigate or press the corresponding key";
        choice = _getch();

        switch (choice) {
        case (int)menuKeys::UP + GameConfig::CAPITAL:
        case (int)menuKeys::UP:
            if (firstTime && selectedOption == (int)menuOptions::Continue + 1)
                selectedOption = (int)menuOptions::Continue - 1;
            else
                selectedOption == 0 ? selectedOption = NUM_OF_MENU_ITEMS : selectedOption--;
            break;
        case (int)menuKeys::DOWN + GameConfig::CAPITAL:
        case (int)menuKeys::DOWN:
            if (firstTime && selectedOption == (int)menuOptions::Continue - 1)
                selectedOption = (int)menuOptions::Continue + 1;
            else
                selectedOption == NUM_OF_MENU_ITEMS ? selectedOption = 0 : selectedOption++;
            break;
        case 'A':
        case 'B':
        case 'C': choice -= (GameConfig::CAPITAL);
        case 'a':
        case 'b':
        case 'c':
            bot_level = choice;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
            selectedOption = choice - '0';
            choice = (int)menuKeys::ENTER;
            break;
        case '4':
            if (!firstTime) {
                selectedOption = (int)menuOptions::Continue;
                choice = (int)menuKeys::ENTER;
            }
            break;
        case '6':
            selectedOption = (int)menuOptions::Level;
            choice = (int)menuKeys::ENTER;
            break;
        case '7':
            selectedOption = (int)menuOptions::Colors;
            choice = (int)menuKeys::ENTER;
            break;
        case '8':
            selectedOption = (int)menuOptions::Instructions;
            choice = (int)menuKeys::ENTER;
            break;
        case '9':
        case (int)menuKeys::ESC:
            selectedOption = (int)menuOptions::Exit;
            choice = (int)menuKeys::ENTER;
        default: break;
        }

        if (choice == (int)menuKeys::ENTER) {
            switch (menuOptions(selectedOption)) {
            case menuOptions::SinglePlayer:
                twoGames = false;
                bot2 = false;
                bot1 = false;
                break;
            case menuOptions::TwoPlayer:
                twoGames = true;
                bot2 = false;
                bot1 = false;
                break;
            case menuOptions::OnePlayerOneBot:
                twoGames = true;
                bot2 = true;
                bot1 = false;
                break;
            case menuOptions::TwoBots:
                twoGames = true;
                bot2 = true;
                bot1 = true;
                break;
            case menuOptions::Level:
                bot_level++;
                if (bot_level > 'c') bot_level = 'a';
                break;
            case menuOptions::Colors:
                color_mod = !color_mod;
                break;
            case menuOptions::Instructions:
                showInstructions();
                break;
            default: break;
            }
        }

    } while (!(choice == (int)menuKeys::ENTER) || ((int)menuOptions::Continue < selectedOption && selectedOption < (int)menuOptions::Exit));
    if (selectedOption == (int)menuOptions::Exit) {
        exit = true;
        system("cls");
        setColor(0x07);
        return false;
    }
    system("cls");
    return selectedOption == (int)menuOptions::Continue ? true : false;
}

void Menu::showInstructions() const  {
    system("cls");
    std::cout << "                              GAME INSTRUCTIONS:  " << std::endl << std::endl;
    std::cout << "         Arrange falling tetrominoes to create complete horizontal lines." << std::endl;
    std::cout << "        Use your keys to move left, right, rotate the shapes or drop them." << std::endl;
    std::cout << "             When you fill horzintal lines cleared and you score pooint." << std::endl;
    std::cout << "                      The game speeds up as you progress." << std::endl;
    std::cout << "           Prevent the blocks from reaching the top to continue playing." << std::endl << std::endl;
    std::cout << "                                    CONTROLS:" << std::endl << std::endl;
    std::cout << "                              Player One:          |      Player Two:" << std::endl;
    std::cout << "       Left:                           A           |               J" << std::endl<< std::endl;
    std::cout << "       Right:                          D           |               L" << std::endl<< std::endl;
    std::cout << "       Rotate Clockwise:               S           |               K" << std::endl<< std::endl;
    std::cout << "       Rotate Counter-Clockwise:       W           |               I" << std::endl<< std::endl;
    std::cout << "       Drop:                           X           |               M" << std::endl<< std::endl;
    std::cout << "       Pause Game:                    ESC          |              ESC" << std::endl << std::endl;
    std::cout << "      press any key to return to menu ";
    char choice = _getch();
};

void Menu::menuTitle(bool color_mod) {
    setColor(Point::getColor(color_mod ? GameConfig::COLOR_TEXT : 0x0F));
    std::cout << "       ##########  ##########  ##########  ########    ######  ##########" << std::endl;
    std::cout << "           ##      ##              ##      ##      ##    ##    ###       " << std::endl;
    std::cout << "           ##      #######         ##      ########      ##    ##########" << std::endl;
    std::cout << "           ##      ##              ##      ##      ##    ##            ##" << std::endl;
    std::cout << "           ##      ##########      ##      ##      ##  ######  ##########\n" << std::endl;
    setColor(Point::getColor(GameConfig::SPACE));
}