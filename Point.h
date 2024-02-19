#ifndef TETRIS_POINT_H
#define TETRIS_POINT_H

#include <iostream>
#include <Windows.h>
#include "general.h"


class Point {
public:
	Point(bool game = true, bool* color_mod = nullptr) { isGame1 = game; this->color_mod = color_mod; }

	Point operator=(const Point& p) {
		color_mod = p.color_mod;
		isGame1 = p.isGame1;
		return this;
	}

	bool isGame1;
	bool* color_mod;

	enum class color {};

	int x;
	int y;


	static constexpr int MIN_Y = 3;
	static constexpr int MIN_X1 = 2;
	static constexpr int MIN_X2 = 40;

	void init(int x, int y) ;
	void draw(char ch) const;
	static int getColor(char c);
};

#endif

