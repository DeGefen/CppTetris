#ifndef __GENERAL_H
#define __GENERAL_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
using namespace std;

#define GAME_HEIGHT 18
#define GAME_WIDTH 12
#define STARTING_X_POSITION 5
#define STARTING_Y_POSITION 19
#define SPACE ' '
#define NUM_OF_CORDS 3
void gotoxy(int, int);
void clrscr();

#endif // __GENERAL_H