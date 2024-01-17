#include "point.h"
#include "GamesManagement.h"
#include "general.h"

#include <iostream>
#include <Windows.h>
using namespace std;

void Point::init(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Point::draw(char ch) {
	int backcolor = getColor(ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
	if (isGame1) gotoxy(x + MIN_X1, y + MIN_Y);
	else gotoxy(x + MIN_X2, y + MIN_Y);
	cout << ch;
}
