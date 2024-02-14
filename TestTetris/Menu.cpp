#include "Menu.h"

void Menu::loading_screen() {
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

void Menu::displayMenu(int selectedOption, char& bot_level, bool firstTime) {
    std::string menuOptionsNames[] = { "(0) Start a new game - Single Player", "(1) Start a new game - Human vs Human", "(2) Start a new game - Human vs Computer", "(3) Start a new game - Computer vs Computer", "(4) - Continue a paused game", "(6) - TetroBot level","(7) - COLORS", "(8) - INSTRUCTIONS", "(9) - EXIT" };
    std::string toggleNames[] = { "OFF", "ON"};
    std::string Levels[] = { "(a) BEST", "(b) GOOD", "(c) NOVICE" };
    system("cls");
    menuTitle();

    for (int i = 0; i <= NUM_OF_MENU_ITEMS; ++i) {
            setColor(selectedOption == i ? 10 : 7); // 10 is green, 7 is default color
            if (i == 6) {
                std::cout << "                    " << menuOptionsNames[i] << ": " << toggleNames[colorsOn] << "\n\n";
            }                                 
            else if (i == 5) {
                std::cout << "                    " << menuOptionsNames[i] << ": ";
                setColor(bot_level == 'a' ? 10 : 7);
                std::cout << Levels[0] << "  ";
                setColor(bot_level == 'b' ? 10 : 7);
                std::cout << Levels[1] << "  ";
                setColor(bot_level == 'c' ? 10 : 7);
                std::cout << Levels[2] << "\n\n";
            }
            else if (i == 4 && firstTime) {       
            }                                    
            else {                               
                std::cout << "                    " << menuOptionsNames[i] << "\n\n";
            }
    }
    setColor(7); // Reset to default color
}

bool Menu::menuControl(bool& twoGames, bool& exit, bool& bot1, bool& bot2, char& bot_level, bool firstTime) {
    char choice;
    int selectedOption = 0;
    menuTitle();
    setColor(0);

    do {
        displayMenu(selectedOption, bot_level, firstTime);
        std::cout << "\n Use W, S and ENTER to navigate or press the corresponding key";
        choice = _getch();

        switch (choice) {
        case (int)menuKeys::UP:
            if (firstTime && selectedOption == 5)
                selectedOption = 3;
            else
                selectedOption == 0 ? selectedOption = NUM_OF_MENU_ITEMS : selectedOption--;
            break;
        case (int)menuKeys::DOWN:
            if (firstTime && selectedOption == 3)
                selectedOption = 5;
            else
                selectedOption == NUM_OF_MENU_ITEMS ? selectedOption = 0 : selectedOption++;
            break;
        case 'A':
        case 'B':
        case 'C': choice -= ('A' - 'a');
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
                selectedOption = 4;
                choice = (int)menuKeys::ENTER;
            }
            break;
        case '6':
            selectedOption = 5;
            choice = (int)menuKeys::ENTER;
            break;
        case '7':
            selectedOption = 6;
            choice = (int)menuKeys::ENTER;
            break;
        case '8':
            selectedOption = 7;
            choice = (int)menuKeys::ENTER;
            break;
        case '9':
        case (int)menuKeys::ESC:
            selectedOption = 8;
            choice = (int)menuKeys::ENTER;
        default: break;
        }

        if (choice == (int)menuKeys::ENTER) {
            switch (selectedOption) {
            case 0:
                twoGames = false;
                bot2 = false;
                bot1 = false;
                break;
            case 1:
                twoGames = true;
                bot2 = false;
                bot1 = false;
                break;
            case 2:
                twoGames = true;
                bot2 = true;
                bot1 = false;
                break;
            case 3:
                twoGames = true;
                bot2 = true;
                bot1 = true;
                break;
            case 5:
                bot_level++;
                if (bot_level > 'c') bot_level = 'a';
                break;
            case 6:
                colorsOn = !colorsOn;
                getColor(COLOR_MOD);
                break;
            case 7:
                showInstructions();
                break;
            default: break;
            }
        }

    } while (!(choice == (int)menuKeys::ENTER) || ( 4 < selectedOption && selectedOption < NUM_OF_MENU_ITEMS ));
    if (selectedOption == NUM_OF_MENU_ITEMS) {
        exit = true;
        system("cls");
        setColor(0x07);
        return false;
    }
    system("cls");
    return selectedOption == 4 ? true : false;
}

void Menu::showInstructions() {
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

void Menu::menuTitle() {
    setColor(getColor(COLOR_TEXT));
    std::cout << "       ##########  ##########  ##########  ########    ######  ##########" << std::endl;
    std::cout << "           ##      ##              ##      ##      ##    ##    ###       " << std::endl;
    std::cout << "           ##      #######         ##      ########      ##    ##########" << std::endl;
    std::cout << "           ##      ##              ##      ##      ##    ##            ##" << std::endl;
    std::cout << "           ##      ##########      ##      ##      ##  ######  ##########\n\n" << std::endl;
    setColor(getColor(' '));
}