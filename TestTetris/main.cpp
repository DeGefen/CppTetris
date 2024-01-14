#include <Windows.h>
#include "MasterHeader.h"
#include "GamesManagement.h"
using namespace std;

int main() {
	GamesManagement games;
	games.drawBorders();
	Clock clock;
	clock.addMiliSeconds(0);
	for (int i = 0; i < 30; i++) {
		clock.addMiliSeconds(500);
	}
	//Board b;
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	//cout << b.count() << endl;
	//Tetromino t;
	//t.setTetro(5);
	//t.jumpTo(5, 0);
	//t.draw();
	//while (t.move(b)) {
	//	t.sideMove(b, 1);
	//cout << b.count() << endl;
	//clock.addMiliSeconds(500);
	//}
	//
	//t.erase();
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	//cout << b.count() << endl;
	//Point p;
	//p.init(1, 1);
	//p.draw('J');
}
