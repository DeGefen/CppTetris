#ifndef TETRIS_CLOCK_H
#define TETRIS_CLOCK_H

#include "general.h"
#include "Point.h"

class Clock {
	unsigned int miliSeconds = 0;
	unsigned int seconds = 0;
	unsigned int minutes = 0;
	int min_x = 1;
	int min_y = 22;
public:
	void addMiliSeconds(unsigned int ms);
	void drawClock(int minx, int miny) const ;
	void reset();
};

#endif