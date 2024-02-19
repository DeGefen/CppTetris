#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include "Point.h"
#include "general.h"
#include <conio.h>

class Menu {

	static constexpr int NUM_OF_MENU_ITEMS = 8;

	enum class menuKeys { UP = 'w', DOWN = 's', ENTER = 13, ESC = 27 };
	enum class menuOptions { SinglePlayer, TwoPlayer, OnePlayerOneBot, TwoBots, Continue, Level ,Colors, Instructions, Exit};


	void displayMenu(int selectedOption, char& bot_level, bool firstTime, bool color_mod);
	void menuTitle(bool color_mod) ;
	void showInstructions() const;

public:
	void loading_screen() const;
	bool menuControl(bool& twoGames, bool& exit, bool& bot1, bool& bot2, char& bot_level, bool firstTime, bool& color_mod); // Return true if player selects continue, otherwise start new game
	void setColor(int colorCode);
};
#endif //TETRIS_MENU_H