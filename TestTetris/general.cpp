#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
using namespace std;

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
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
	case 'G':
		color = 0x88;
		break;
	case 'g':
		color = 0x08;
		break;
	case ' ':
		color = 0x00;
		break;
	case '@':
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