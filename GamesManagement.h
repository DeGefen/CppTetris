#ifndef TETRIS_GAMESMANAGEMENT_H
#define TETRIS_GAMESMANAGEMENT_H

#include "Menu.h"
#include <conio.h>
#include <cstdlib>
#include "GameMech.h"
#include "Clock.h"
#include "Windows.h"
#include "Menu.h"
#include "GoodPosition.h"
#include "Tetrobot.h"

class GamesManagement {
public:
    void start();
    GamesManagement operator=(const GamesManagement& games) = delete;

private:
    static constexpr bool _GAME_BORDER = 1;
    static constexpr bool _NEXT_TETRO_BORDER = 0;

    static constexpr int _SPEED_UP = 100;
    static constexpr int _MAX_SPEED = 5;
    static constexpr int _DEFAULT_SPEED = 20;
    static constexpr int _THRESHHOLD = 7;

    GameMech game1;
    GameMech game2;
    TetroBot bot1;
    TetroBot bot2;
    Clock clock;
    Menu menu;

    int counter;
    int speed;
    int reachedThreshHold;
    int bot_mod;
    char bot_level;
    bool exit;
    bool twoGames;
    bool dropped1;
    bool dropped2;
    bool game1_alive = false;
    bool game2_alive;
    bool isBot1;
    bool isBot2;
    bool bot1_down;
    bool bot2_down;
    bool *color_mod;

    void drawBorders(char color = GameConfig::COLOR_BORDER);
    void drawBordersAUX(int minx, int miny, bool isGameBorder, char color);
    void movment(int key, int mode=0);
    void lunch();
    void endGame();
    void winner(int i);
    void runGames();
};
#endif
