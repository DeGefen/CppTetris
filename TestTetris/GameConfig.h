#pragma once

class GameConfig {
public:
    enum class eKeys1 { LEFT = 'a', RIGHT = 'd', ROTATE_CLOCKWISE = 's', ROTATE_COUNTERCLOCKWISE = 'w', DROP = 'x', ESC = 27 };
    enum class eKeys2 { LEFT = 'j', RIGHT = 'l', ROTATE_CLOCKWISE = 'k', ROTATE_COUNTERCLOCKWISE = 'i', DROP = 'm', ESC = 27 };
    
    enum class configs {IsGame1, ColorMod};

    static constexpr int NUM_OF_CORDS = 4;
    static constexpr int NULL_VALUE = -4;
    static constexpr int BOMB_RADIUS = 4;

    static constexpr int GAME_HEIGHT = 18;
    static constexpr int GAME_WIDTH = 12;
    static constexpr int NEXT_TET_HEIGHT = 8;
    static constexpr int NEXT_TET_WIDTH = 8;

    static constexpr int CAPITAL = 'A' - 'a';
    static constexpr int SPACE = ' ';
    static constexpr int BOMB = 'B';
    static constexpr int BOOM = '!';
    static constexpr int BAM = '#';
    static constexpr int COLOR_BORDER = 'G';
    static constexpr int COLOR_INFO = 'g';
    static constexpr int COLOR_TEXT = 'w';

    static constexpr int STARTING_X = 5;
    static constexpr int STARTING_Y = -1;
    static constexpr int NEXT_X = 21;
    static constexpr int NEXT_Y = 3;

    static constexpr bool IS_GAME1 = true;
    static constexpr bool IS_GAME2 = false;

    static constexpr bool START_NEW_GAME = true;
};