#include "Menu.h"
#include "Windows.h"
#include "stdlib.h"


void louding_screen() {
    srand(time(0));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
	gotoxy(0, 5);
    std::cout << "  /////////////////   /////////////////   /////////////////   ////////////////   /////   ///////////////// " << std::endl;
    std::cout << "  ################//  ################//  ################//  ###############//  ####//  ################//" << std::endl;
    std::cout << "  ################/   ################/   ################/   ###############//  ####//  ################/ " << std::endl;
    std::cout << "        ####//        ####//                    ####//        ####//     ####//  ####//  ####//            " << std::endl;
    std::cout << "        ####//        ####/////////////         ####//        ####///////####/   ####//  ####///////////// " << std::endl;
    std::cout << "        ####//        ################//        ####//        ###########//      ####//  ################//" << std::endl;
    std::cout << "        ####//        ################/         ####//        ###########//////  ####//  ################//" << std::endl;
    std::cout << "        ####//        ####//                    ####//        ####//     ####//  ####//              ####//" << std::endl;
    std::cout << "        ####//        ####/////////////         ####//        ####//     ####//  ####//  ////////////####//" << std::endl;
    std::cout << "        ####//        ################//        ####//        ####//     ####//  ####//  ################//" << std::endl;
    std::cout << "        ####/         ################/         ####/         ####/      ####/   ####/   ################/ " << std::endl;
    
    gotoxy(0, 20);

    std::cout << "     ####################################################################################################   " << std::endl;
    std::cout << "     #                                                                                                  #   " << std::endl;
    std::cout << "     ####################################################################################################   " << std::endl;

    gotoxy(6, 21);
    for (int i = 0; i< 96; ++i) {
        Sleep(25+(rand()%50));
        std::cout << '|';
    }
    Sleep(1300);
    std::cout << '|';
    Sleep(500);
    std::cout << '|';


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
    string menuOptionsNames[] = {"CONTINUE GAME", "START NEW GAME", "COLORS", "TWO PLAYERS MODE", "INSTRUCTIONS", "EXIT"};
    string toggleNames[] = { "OFF", "ON"};
    system("cls");
    std::cout << "\n\n                                              Menu:\n\n";
    for (int i = 0 + firstTime; i < 6; ++i) {
        setColor(selectedOption == i ? 10 : 7); // 10 is green, 7 is default color
        if (i == 2) {
            std::cout << "                                          " << menuOptionsNames[i] <<": " << toggleNames[colorsOn] << "\n\n";
        } else if (i == 3) {
            std::cout << "                                          " << menuOptionsNames[i] << ": " << toggleNames[twoPlayers] << "\n\n";
        }
        else {
            std::cout << "                                          " << menuOptionsNames[i] << "\n\n";
        }  
    }
    setColor(7); // Reset to default color
}

bool menuControl(bool& twoPlayerMode, bool& colorsMode, bool firstTime) {
    setColor(0);
    char choice;
    int selectedOption = 0;
    //bool colorsOn = true;
    //bool twoPlayersOn = true;
    do {
        displayMenu(selectedOption, colorsMode, twoPlayerMode, firstTime);
        std::cout << "\n\n Use W, S and ENTER to navigate ";
        choice = _getch();

        switch (choice) {
        case (int)menuKeys::UP:
            selectedOption == 0 + firstTime ? selectedOption = 5 : selectedOption--;
            break;
        case (int)menuKeys::DOWN:
            selectedOption == 5 ? selectedOption = 0 + firstTime : selectedOption++;
            break;
        case (int)menuKeys::ESC:
            selectedOption = 5;
            break;
        case(int)menuKeys::ENTER:
            if (selectedOption == 2) {
                colorsMode = !colorsMode;
                getColor('@');
            } else if (selectedOption == 3) {
                twoPlayerMode = !twoPlayerMode;
            } else if (selectedOption == 4) {
                showInstructions();
            }
            break;
        default:
            break;
        }

    } while (!(choice == 13 && selectedOption != 2 && selectedOption != 3 && selectedOption != 4));
    if (selectedOption == 5) {
        std::exit(0);
    }
    std::cout << "You selected Option " << selectedOption << ".\n";
    system("cls");
    return !selectedOption;
}

void showInstructions() {
    system("cls");
    std::cout << "\n                                           GAME INSTRUCTIONS:  " << std::endl << std::endl;
    std::cout << "               Arrange falling tetrominoes to create complete horizontal lines. Use your keys to " << std::endl;
    std::cout << "               move left, right, rotate the shapes or accelerate the descent. When horzintal lines" << std::endl;
    std::cout << "                                       are complete they are cleared." << std::endl;
    std::cout << "               Clear lines to score points. The game speeds up as you progress. Prevent the blocks " << std::endl;
    std::cout << "                                from reaching the top to continue playing." << std::endl << std::endl;
    std::cout << "                                               CONTROLS:" << std::endl << std::endl;
    std::cout << "                                 Player One:       |       Player Two (In two players mode):" << std::endl;
    std::cout << "       Left:                           A           |               J" << std::endl<< std::endl;
    std::cout << "       Right:                          D           |               L" << std::endl<< std::endl;
    std::cout << "       Rotate Clockwise:               S           |               K" << std::endl<< std::endl;
    std::cout << "       Rotate Counter-Clockwise:       W           |               I" << std::endl<< std::endl;
    std::cout << "       Drop:                           X           |               M" << std::endl<< std::endl;
    std::cout << "       Pause Game:                    ESC          |              ESC" << std::endl << std::endl;
    std::cout << "      press any key to return to menu " << std::endl;
    char choice = _getch();
};
