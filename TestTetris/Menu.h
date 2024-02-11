#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include "Point.h"
#include "general.h"
#include <conio.h>


enum class menuKeys { UP = 'w', DOWN = 's', ENTER = 13, ESC = 27 };
enum class menuOptions { START, CONTINUE, COLORS, TWO_PLAYERS_MODE, INSTRUCTIONS, EXIT};

void loading_screen();
void drawMenu(bool newGame = true);
void displayMenu(int selectedOption, bool colorsOn = true, bool firstTime = false, bool bot=false, bool twoBots=false);
bool menuControl(bool& colorsMode, bool& exit, bool& bot, bool& twoBots, bool firstTime = false); // Return true if player selects continue, otherwise start new game
void setColor(int colorCode);
void showInstructions();
void endScreen();
void startGame();
void pauseGame();
void returnToGame();
void colorGame(bool withColor);
void winner(bool game1, bool game2);
void menuTitle();
#endif //TETRIS_MENU_H