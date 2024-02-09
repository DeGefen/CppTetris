#include "Runner.h"

void Runner::start() {
    //loading_screen();
    bool twolayerMode = true, colorsMode = true, exit = false, bot = false, twoBots = false, continueGame;
    continueGame = menuControl(colorsMode, exit ,bot, twoBots, true);
    if (exit) return;
    while (true) {
        if (continueGame && !exit)
            menuControl(colorsMode, exit, bot, twoBots, true);
        if (exit) return;
        GamesManagement gamesManage(twolayerMode);
        gamesManage.drawBorders();
        gamesManage.runGames(continueGame, bot, twoBots, colorsMode , exit);
    }
}