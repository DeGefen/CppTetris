#pragma once

//#include "GameMech.h"

class Point {
	int x;
	int y;
	bool isGame1;


public:
	Point(bool game = true) { isGame1 = game; }

	static constexpr int MIN_Y = 2;
	static constexpr int MIN_X1 = 9;
	static constexpr int MIN_X2 = 55;

	void init(int x, int y);
	void draw(char ch);
};

