#include "Runner.h"

void Runner::start() {
    louding_screen();
    bool twolayerMode = true, colorsMode = true, exit = false, continueGame;
    continueGame = menuControl(twolayerMode, colorsMode, exit ,true);
    if (exit) return;
    while (true) {
        if (continueGame && !exit)
            menuControl(twolayerMode, colorsMode, exit, true);
        if (exit) return;
        GamesManagement gamesManage(twolayerMode);
        gamesManage.drawBorders();
        gamesManage.runGames(continueGame, twolayerMode, colorsMode , exit);
    }
}