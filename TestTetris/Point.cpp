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
	diff_x = 1;
	diff_y = 0;
}
void Point::draw(char ch)
{
	int backcolor = getColor(ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
	gotoxy(x + GameMech::MIN_X - 1, y + GameMech::MIN_Y - 1);
	cout << ch;
}


//void Point::move(GamesManagement::eKeys key)
//{
//	switch (key)
//	{
//	case GamesManagement::eKeys::LEFT:
//		diff_x = -1;
//		diff_y = 0;
//		break;
//	case GamesManagement::eKeys::RIGHT:
//		diff_x = 1;
//		diff_y = 0;
//		break;
//	case GamesManagement::eKeys::UP:
//		diff_x = 0;
//		diff_y = -1;
//		break;
//	case GamesManagement::eKeys::DOWN:
//		diff_x = 0;
//		diff_y = 1;
//		break;
//	}
//
//	x += diff_x;
//	if (x > GamesManagement::GAME_WIDTH)
//		x = 1;
//	else if (x == 0)
//		x = GamesManagement::GAME_WIDTH;
//
//	y += diff_y;
//	if (y > GamesManagement::GAME_HEIGHT)
//		y = 1;
//	else if (y == 0)
//		y = GamesManagement::GAME_HEIGHT;
//}
