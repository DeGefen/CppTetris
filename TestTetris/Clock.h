#pragma once
#include <Windows.h>
#include "general.h"

class Clock {
	unsigned int miliSeconds = 0;
	unsigned int seconds = 0;
	unsigned int minutes = 0;
	//unsigned int buffer = 1000;
	int min_x = 40;
	int min_y = 2;
public:
	void addMiliSeconds(unsigned int ms);
	void drawClock(int minx, int miny);
	void reset();

	//unsigned int getBuffer();
};