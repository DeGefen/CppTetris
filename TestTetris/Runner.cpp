#include "Runner.h"

void Runner::start() {
    louding_screen();
    bool twolayerMode = true, colorsMode = true,  continueGame;
    continueGame = menuControl(twolayerMode, colorsMode, true);
    while (true) {
        if (continueGame)
            menuControl(twolayerMode, colorsMode, true);
        GamesManagement gamesManage(twolayerMode);
        gamesManage.drawBorders();
        gamesManage.runGames(continueGame, twolayerMode, colorsMode);
    }
}