#ifndef __MENU_H
#define __MENU_H

#include "Point.h"
#include "general.h"
#include <conio.h>


enum class menuKeys { UP = 'w', DOWN = 's', ENTER = 13, ESC = 27 };
enum class menuOptions { CONTINUE, START, COLORS, TWO_PLAYERS_MODE, INSTRUCTIONS, EXIT};

void louding_screen(int n);
void drawMenu(bool newGame = true);
void displayMenu(int selectedOption, bool colorsOn = true, bool twoPlayers = true,  bool firstTime = false);
bool menuControl(bool& twoPlayerMode, bool& colorsMode, bool firstTime = false); // Return true if player selects continue, otherwise start new game
void setColor(int colorCode);
void showInstructions();
void endScreen();
void startGame();
void pauseGame();
void returnToGame();
void colorGame(bool withColor);
#endif //__MENU_H