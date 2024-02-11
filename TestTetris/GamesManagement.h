#ifndef TETRIS_GAMESMANAGEMENT_H
#define TETRIS_GAMESMANAGEMENT_H

#include <conio.h>
#include <cstdlib>
#include "GameMech.h"
#include "Clock.h"
#include "Windows.h"
#include "Menu.h"
#include "GoodPosition.h"
#include "Tetrobot.h"
//#include "GoodPositionNode.h"

enum class eKeys1 { LEFT = 'a', RIGHT = 'd', ROTATE_CLOCKWISE = 's', ROTATE_COUNTERCLOCKWISE = 'w', DROP = 'x', ESC = 27 };
enum class eKeys2 { LEFT = 'j', RIGHT = 'l', ROTATE_CLOCKWISE = 'k', ROTATE_COUNTERCLOCKWISE = 'i', DROP = 'm', ESC = 27 };

class GamesManagement {
public:
    GamesManagement(bool isTwoGames= true) { lunch(isTwoGames); }
    void drawBorders(char color = COLOR_BORDER);
    void runGames(bool& continueGame, bool& bot, bool& twoBots, bool& colorsMode, bool& exit);

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
    bool game1_alive;
    bool game2_alive;
    bool bot;
    bool twoBots;

    void drawBordersAUX(int minx, int miny, bool isGameBorder, char color);
    void FlashBoarder();
    void movment(int key);
    void lunch(bool isTwoGames = true);
    void endGame();
    //void movment(char key);
    void winner(int i);
    int getBotMove(bool isGame2 = true);
};
#endif
