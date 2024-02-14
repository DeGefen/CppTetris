#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include "Point.h"
#include "general.h"
#include <conio.h>

class Menu {

	static constexpr int NUM_OF_MENU_ITEMS = 8;

	enum class menuKeys { UP = 'w', DOWN = 's', ENTER = 13, ESC = 27 };
	enum class menuOptions { START, CONTINUE, COLORS, TWO_PLAYERS_MODE, INSTRUCTIONS, EXIT };

	bool colorsOn = true;

	void displayMenu(int selectedOption, char& bot_level, bool firstTime = false);
	void menuTitle();
	void showInstructions();

public:

	void loading_screen();
	bool menuControl(bool& twoGames, bool& exit, bool& bot1, bool& bot2, char& bot_level, bool firstTime = false); // Return true if player selects continue, otherwise start new game
	void setColor(int colorCode);
};
#endif //TETRIS_MENU_H