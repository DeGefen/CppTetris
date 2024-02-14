#ifndef TETRIS_GENERAL_H
#define TETRIS_GENERAL_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include "GameConfig.h"

constexpr auto COLOR_MOD = '@';
constexpr auto COLOR_BORDER = 'G';
constexpr auto COLOR_INFO = 'g';
constexpr auto COLOR_TEXT = 'w';


void gotoxy(int, int);
void clrscr();
int getColor(char c);

#endif // TETRIS_GENERAL_H