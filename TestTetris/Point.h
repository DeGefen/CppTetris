#ifndef TETRIS_POINT_H
#define TETRIS_POINT_H

#include <iostream>
#include <Windows.h>
#include "general.h"
using namespace std;


class Point {
	bool isGame1;


public:

	int x;
	int y;

	Point(bool game = true) { isGame1 = game; }

	static constexpr int MIN_Y = 3;
	static constexpr int MIN_X1 = 2;
	static constexpr int MIN_X2 = 40;

	void init(int x, int y);
	void draw(char ch);
};

#endif

