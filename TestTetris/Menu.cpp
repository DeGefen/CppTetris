#include "Menu.h"

void loading_screen() {
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

void drawMenu(bool newGame) {
    if(newGame)
        std::cout << "Start Game" << std::endl;
    else {
        std::cout << "Continue Game" << std::endl;
        std::cout << "Start A New Game" << std::endl;
    }

    std::cout << "Colors:   ON | OFF" << std::endl;
    std::cout << "Instructions" << std::endl;
    std::cout << "Exit" << std::endl;


    while (true) {
        int keyPressed = 0;
        if (_kbhit()) {
            keyPressed = _getch();
            if (keyPressed == (int)menuKeys::ESC)
                break;
        }
        Sleep(500);
    
    }

}

void endScreen() {

    setColor(7);
    system("cls");                                          
    std::cout << "\n\n\n\n\n\n\n                                           Tetrip :(" << std::endl;
    Sleep(2000);
}


void setColor(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

void displayMenu(int selectedOption, bool colorsOn, bool twoPlayers, bool firstTime) {
    string menuOptionsNames[] = {"(1) - START NEW GAME", "(2) - CONTINUE GAME", "(6) - COLORS", "(7) - TWO PLAYERS MODE", "(8) - INSTRUCTIONS", "(9) - EXIT"};
    string toggleNames[] = { "OFF", "ON"};
    system("cls");
    menuTitle();

    for (int i = 0; i < 6; ++i) {
            setColor(selectedOption == i ? 10 : 7); // 10 is green, 7 is default color
            if (i == 2) {
                std::cout << "                             " << menuOptionsNames[i] << ": " << toggleNames[colorsOn] << "\n\n";
            }
            else if (i == 3) {
                std::cout << "                             " << menuOptionsNames[i] << ": " << toggleNames[twoPlayers] << "\n\n";
            }
            else if (i == 1 && firstTime) {
            }
            else {
                std::cout << "                             " << menuOptionsNames[i] << "\n\n";
            }
    }
    setColor(7); // Reset to default color
}

bool menuControl(bool& twoPlayerMode, bool& colorsMode, bool& exit, bool firstTime) {
    char choice;
    int selectedOption = 0;
    menuTitle();
    setColor(0);

    do {
        displayMenu(selectedOption, colorsMode, twoPlayerMode, firstTime);
        std::cout << "\n\n Use W, S and ENTER to navigate or press the corresponding numbers";
        choice = _getch();

        switch (choice) {
        case (int)menuKeys::UP:
            if (firstTime && selectedOption == 2)
                selectedOption = 0;
            else
                selectedOption == 0 ? selectedOption = 5 : selectedOption--;
            break;
        case (int)menuKeys::DOWN:
            if (firstTime && selectedOption == 0)
                selectedOption = 2;
            else
              selectedOption == 5 ? selectedOption = 0 : selectedOption++;
            break;
        case (int)menuKeys::ESC:
            selectedOption = 5;
            break;
        case(int)menuKeys::ENTER:
            if (selectedOption == 2) {
                colorsMode = !colorsMode;
                getColor(COLOR_MOD);
            } else if (selectedOption == 3) {
                twoPlayerMode = !twoPlayerMode;
            } else if (selectedOption == 4) {
                showInstructions();
            }
            break;
        case '1':
            selectedOption = 0;
            choice = (int)menuKeys::ENTER;
            break;
        case '2':
            if (!firstTime) {
                selectedOption = 1;
            }
            choice = (int)menuKeys::ENTER;
            break;
        case '6':
            selectedOption = 2;
            colorsMode = !colorsMode;
            getColor('@');
            break;
        case '7':
            selectedOption = 3;
            twoPlayerMode = !twoPlayerMode;
            break;
        case '8':
            selectedOption = 4;
            showInstructions();
            break;
        case '9':
            selectedOption = 5;
            exit = true;
            choice = (int)menuKeys::ENTER;
            break;
        default:
            break;
        }

    } while (!((choice == (int)menuKeys::ENTER) && selectedOption != 2 && selectedOption != 3 && selectedOption != 4));
    if (selectedOption == 5) {
        exit = true;
        system("cls");
        setColor(0x07);
        return 0;
    }
    system("cls");
    return selectedOption;
}

void showInstructions() {
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

void menuTitle() {
    setColor(getColor(COLOR_TEXT));
    std::cout << "\n" << std::endl;
    std::cout << "       ##########  ##########  ##########  ########    ######  ##########" << std::endl;
    std::cout << "           ##      ##              ##      ##      ##    ##    ###       " << std::endl;
    std::cout << "           ##      #######         ##      ########      ##    ##########" << std::endl;
    std::cout << "           ##      ##              ##      ##      ##    ##            ##" << std::endl;
    std::cout << "           ##      ##########      ##      ##      ##  ######  ##########\n\n" << std::endl;
    setColor(getColor(' '));
}