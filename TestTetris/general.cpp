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
	int color;
	switch (c) {
	case 'I':
		color = 0xBF;
		break;
	case 'O':
		color = 0xEF;
		break;
	case 'T':
		color = 0x5F;
		break;
	case 'J':
		color = 0x1F;
		break;
	case 'L':
		color = 0x6F;
		break;
	case 'S':
		color = 0xAF;
		break;
	case 'Z':
		color = 0x4F;
		break;
	case 'G':
		color = 0x808080;
		break;
	default:
		color = 0;
		break;
	}
	return color;
};