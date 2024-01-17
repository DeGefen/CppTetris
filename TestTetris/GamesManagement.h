#ifndef TETRIS_GAMESMANAGEMENT_H
#define TETRIS_GAMESMANAGEMENT_H

#include <conio.h>
#include <cstdlib>
#include "GameMech.h"
#include "Clock.h"
#include "Windows.h"
#include "Menu.h"

enum class eKeys1 { LEFT = 'a', RIGHT = 'd', ROTATE_CLOCKWISE = 's', ROTATE_COUNTERCLOCKWISE = 'w', DROP = 'x', ESC = 27 };
enum class eKeys2 { LEFT = 'j', RIGHT = 'l', ROTATE_CLOCKWISE = 'k', ROTATE_COUNTERCLOCKWISE = 'i', DROP = 'm', ESC = 27 };

class GamesManagement {
public:
    GamesManagement(bool isTwoGames= true) { lunch(isTwoGames); }
    void runGames();

private:
    static constexpr int CAPITAL = 'A' - 'a';
    static constexpr int _LEFT = -1;
    static constexpr int _RIGHT = 1;
    static constexpr int _ROTATE_CLOCKWISE = -1;
    static constexpr int _ROTATE_COUNTERCLOCKWISE = 1;
    static constexpr bool _GAME_BORDER = 1;
    static constexpr bool _NEXT_TETRO_BORDER = 0;


    static constexpr int _SPEED_UP = 100;
    static constexpr int _MAX_SPEED = 3;
    static constexpr int _DEFAULT_SPEED= 10;


    GameMech game1;
    GameMech game2;
    Clock clock;
    int counter;
    int threshHold;
    int reachedThreshHold;
    bool twoGames;
    bool dropped1;
    bool dropped2;

    void drawBordersAUX(int minx, int miny, bool isGameBorder);
    void movment(int key);
    void lunch(bool isTwoGames = true);
    void drawBorders();
};
#endif
