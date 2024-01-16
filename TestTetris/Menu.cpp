#include "Menu.h"
#include "Windows.h"
#include "stdlib.h"


void louding_screen(int n) {
    srand(time(0));
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
	gotoxy(0, 5);
    std::cout << "//////////////////    //////////////////    //////////////////    /////////////////    //////     ///////////////// " << std::endl;
    std::cout << "#################//   #################//   #################//   ################//   #####//   #################//" << std::endl;
    std::cout << "#################/    #################/    #################/    ################//   #####//   #################/ " << std::endl;
    std::cout << "      #####//         #####//                     #####//         #####//    #####//   #####//   #####//            " << std::endl;
    std::cout << "      #####//         #####/////////////          #####//         #####//////#####/    #####//   #####///////////// " << std::endl;
    std::cout << "      #####//         #################//         #####//         ###########//        #####//   #################//" << std::endl;
    std::cout << "      #####//         #################/          #####//         ###########//////    #####//   #################//" << std::endl;
    std::cout << "      #####//         #####//                     #####//         #####//    #####//   #####//               #####//" << std::endl;
    std::cout << "      #####//         #####/////////////          #####//         #####//    #####//   #####//   ////////////#####//" << std::endl;
    std::cout << "      #####//         #################//         #####//         #####//    #####//   #####//   #################//" << std::endl;
    std::cout << "      #####/          #################/          #####/          #####/     #####/    #####/    #################/ " << std::endl;
    
    gotoxy(0, 20);

    std::cout << "   ##############################################################################################################   " << std::endl;
    std::cout << "   #                                                                                                            #   " << std::endl;
    std::cout << "   ##############################################################################################################   " << std::endl;

    gotoxy(4, 21);
    for (int i = 0; i< 106; ++i) {
        Sleep(50+(rand()%200));
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
    std::cout << "Tetrip :(" << std::endl;
}


void setColor(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

void displayMenu(int selectedOption, bool colorsOn, bool twoPlayers) {
    string menuOptionsNames[] = {"CONTINUE GAME", "START NEW GAME", "COLORS", "TWO PLAYERS MODE", "INSTRUCTIONS", "EXIT"};
    string toggleNames[] = { "OFF", "ON"};
    system("cls");  // Clear the screen (works on Windows, may need adjustment for other platforms)
    std::cout << "Menu:\n";
    for (int i = 0; i < 6; ++i) {
        setColor(selectedOption == i ? 10 : 7); // 10 is green, 7 is default color
        if (i == 2) {
            std::cout << menuOptionsNames[i] <<": " << toggleNames[colorsOn] << "\n";
        } else if (i == 3) {
            std::cout << menuOptionsNames[i] << ": " << toggleNames[twoPlayers] << "\n";
        }
        else {
            std::cout << menuOptionsNames[i] << "\n";
        }  
    }
    setColor(7); // Reset to default color
}

int menuControl() {
    char choice;
    int selectedOption = 0;
    bool colorsOn = true;
    bool twoPlayersOn = true;
    do {
        displayMenu(selectedOption, colorsOn, twoPlayersOn);
        std::cout << "\n\n Use W, S and ENTER to navigate ";
        choice = _getch();

        switch (choice) {
        case (int)menuKeys::UP:
            selectedOption == 0 ? selectedOption = 5 : selectedOption--;
            break;
        case (int)menuKeys::DOWN:
            selectedOption == 5 ? selectedOption = 0 : selectedOption++;
            break;
        case (int)menuKeys::ESC:
            selectedOption = 5;
            break;
        case(int)menuKeys::ENTER:
            if (selectedOption == 2) {
                colorsOn = !colorsOn;
                // TODO: toggle colors here
            } else if (selectedOption == 3) {
                twoPlayersOn = !twoPlayersOn;
                // TODO: toggle twoPlayersOn here
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
    return selectedOption;
}

void showInstructions() {
    system("cls");
    std::cout << "                                           GAME INSTRUCTIONS:  " << std::endl << std::endl;
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

    //std::cout << "      #####//         #####/////////////          #####//         #####//////#####/    #####//   #####///////////// " << std::endl;
    //std::cout << "      #####//         #################//         #####//         ###########//        #####//   #################//" << std::endl;
    //std::cout << "      #####//         #################/          #####//         ###########//////    #####//   #################//" << std::endl;
    //std::cout << "      #####//         #####//                     #####//         #####//    #####//   #####//               #####//" << std::endl;
    //std::cout << "      #####//         #####/////////////          #####//         #####//    #####//   #####//   ////////////#####//" << std::endl;
    //std::cout << "      #####//         #################//         #####//         #####//    #####//   #####//   #################//" << std::endl;
    std::cout << "      press any key to return to menu " << std::endl;
    char choice = _getch();
};
