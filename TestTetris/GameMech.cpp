#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include "general.h"
#include "GamesManagement.h"

//void gotoxy(int x, int y)
//{
//    HANDLE hConsoleOutput;
//    COORD dwCursorPosition;
//    cout.flush();
//    dwCursorPosition.X = x;
//    dwCursorPosition.Y = y;
//    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
//}

//void clrscr()
//{
//    system("cls");
//}

void GameMech::updateScore(int i) {
    switch (i) {
    case 1:
        score += 40;
    case 2:
        score += 100;
    case 3:
        score += 300;
    case 4:
        score += 1200;
    default: {}
    }
}

void GameMech::getNextTet() {
    std::rand();
}

void GameMech::drawBorder() {
    {
        for (int col = GamesManagement::MIN_X; col < GAME_WIDTH + GamesManagement::MIN_X; col++)
        {
            gotoxy(col, GamesManagement::MIN_Y - 1);
            cout << "-";

            gotoxy(col, GAME_HEIGHT + GamesManagement::MIN_Y);
            cout << "-";
        }

        for (int row = GamesManagement::MIN_Y - 1; row <= GAME_HEIGHT + GamesManagement::MIN_Y; row++)
        {
            gotoxy(GamesManagement::MIN_X - 1, row);
            cout << "|";

            gotoxy(GAME_WIDTH + GamesManagement::MIN_X, row);
            cout << "|";
        }
    }
}

void GameMech::init(int num)
{
}

void GameMech::run()
{
}

void GameMech::freeMemory()
{
}
