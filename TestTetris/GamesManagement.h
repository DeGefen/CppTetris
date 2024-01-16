#pragma once
#ifndef TETRIS_GAMESMANAGEMENT_H
#define TETRIS_GAMESMANAGEMENT_H

//#include "Board.h"
#include <conio.h>
#include <cstdlib>
#include "GameMech.h"
#include "Clock.h"
#include "Windows.h"
#include "Menu.h"

enum class eKeys1 { LEFT = 'a', RIGHT = 's', ROTATE_CLOCKWISE = 's', ROTATE_COUNTERCLOCKWISE = 'w', DROP = 'x', ESC = 27 };
enum class eKeys2 { LEFT = 'j', RIGHT = 'l', ROTATE_CLOCKWISE = 'k', ROTATE_COUNTERCLOCKWISE = 'i', DROP = 'm', ESC = 27 };

class GamesManagement {
    GameMech* game1;
    GameMech* game2;
    Clock clock;


public:
    void drawBorders();
    void runGames();
    void movment(char key);
};
#endif
