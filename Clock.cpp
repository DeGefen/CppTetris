#include "Clock.h"

void Clock::addMiliSeconds(unsigned int ms)
{
	Sleep(ms);
	miliSeconds += ms;
	if (miliSeconds >= 1000) {
		seconds += miliSeconds / 1000;
		miliSeconds = miliSeconds % 1000;
	}
	if (seconds > 59) {
		minutes++;
		seconds = 0;
	}
	drawClock(min_x, min_y);
}

void Clock::drawClock(int minx, int miny) const {
	int backcolor = Point::getColor(GameConfig::COLOR_INFO);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
	gotoxy(minx, miny);

	if (minutes < 10) {
		std::cout << '0';
	}
	std::cout << minutes << ":";

	if (seconds < 10) {
		std::cout << '0';
	}
	std::cout << seconds << std::endl;

}

void Clock::reset() {
  miliSeconds = 0;
  seconds = 0;
  minutes = 0;
}