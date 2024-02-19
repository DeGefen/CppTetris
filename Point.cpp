#include "point.h"

void Point::init(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Point::draw(char ch) const{
	int backcolor = (*color_mod) ? getColor(ch): 0x0F;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
	if (isGame1) gotoxy(x + MIN_X1, y + MIN_Y);
	else gotoxy(x + MIN_X2, y + MIN_Y);
	std::cout << ch;
}

int Point::getColor(char c){
	int color = 0x0F;
	switch (c) {
	case 'I':
		color = 0xBB;
		break;
	case 'O':
		color = 0xEE;
		break;
	case 'T':
		color = 0x55;
		break;
	case 'J':
		color = 0x11;
		break;
	case 'L':
		color = 0x66;
		break;
	case 'S':
		color = 0xAA;
		break;
	case 'Z':
		color = 0x44;
		break;
	case GameConfig::BOMB:
		color = 0x40;
		break;
	case GameConfig::COLOR_BORDER:
		color = 0x88;
		break;
	case GameConfig::COLOR_INFO:
		color = 0x08;
		break;
	case GameConfig::COLOR_TEXT:
		color = 0x0A;
		break;
	case ' ':
		color = 0x00;
		break;
	default:
		color = 0x0F;
		break;
	}
	return color;
};