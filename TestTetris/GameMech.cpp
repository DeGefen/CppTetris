#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include <conio.h>
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

//void GameMech::updateScore(int i) {
//    switch (i) {
//    case 1:
//        score += 40;
//    case 2:
//        score += 100;
//    case 3:
//        score += 300;
//    case 4:
//        score += 1200;
//    default: {}
//    }
//}


void GameMech::drawBorder(int minx, int miny, bool isGameBorder) {
    int width = isGameBorder ? GAME_WIDTH : NEXT_TET_WIDTH;
    int height = isGameBorder ? GAME_HEIGHT : NEXT_TET_HEIGHT;
    int backcolor = getColor('G');
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
    {
        for (int col = minx; col < width + minx; col++)
        {
            gotoxy(col, miny - 1);
            cout << "-";

            gotoxy(col, height + miny);
            cout << "-";
        }

        for (int row = miny - 1; row <= height + miny; row++)
        {
            gotoxy(minx - 1, row);
            cout << "|";

            gotoxy(width + minx, row);
            cout << "|";
        }
    }
}

void GameMech::init(Board* board)
{
    //activeLines = board;
}

void GameMech::runGame(Clock* clock, bool p1)
{
    Board board;
    srand((time(0)));
    Tetromino next(rand() % 7);
    Tetromino curr(rand() % 7);
    clock->addMiliSeconds(500);
    curr.jumpTo(MIN_X1-3, 0);
    next.jumpTo(MIN_X1+13, 4);
    curr.draw();
    next.draw();
    while (true) {
        int keyPressed = 0;
        if (_kbhit()) {
            keyPressed = _getch();
            if (keyPressed == (int)eKeys1::ESC)
                break;
        }
        Sleep(500);
        //for (int i = 0; i < numOfSnakes; i++)
        curr.sideMove(board, 1);
            //allSnakes[i].move((GameConfig::eKeys)keyPressed);
    }


}

void GameMech::freeMemory()
{
}
