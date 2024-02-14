#include "general.h"

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void clrscr()
{
	system("cls");
}

int getColor(char c) {
	static bool color_mod = true;
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
	case COLOR_BORDER:
		color = 0x88;
		break;
	case COLOR_INFO:
		color = 0x08;
		break;
	case COLOR_TEXT :
		color = 0x0A;
		break;
	case ' ':
		color = 0x00;
		break;
	case COLOR_MOD:
		if (color_mod) color_mod = false;
		else color_mod = true;
		break;
	default:
		color = 0x0F;
		break;
	}
	if (!color_mod) return 0x0F;
	return color;
};