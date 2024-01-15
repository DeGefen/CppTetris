#include <Windows.h>
#include "MasterHeader.h"
#include "GamesManagement.h"
using namespace std;

int main() {

	GamesManagement games;
	games.runGames();
	Sleep(10000);
	//GameMech gameMech;
	//games.drawBorders();
	//Clock clock;
	//clock.addMiliSeconds(0);
	//Board b;
	////Tetromino *tP;
	////tP = gameMech.getNextTet();
	//Tetromino t;
	////t = *tP;
	//t = gameMech.getNextTet();
	//t.jumpTo(2, 0);
	//t.rotate(b, 1);
	//t.draw();
	//b.draw();
	//while (t.move(b)) {
	//	b.draw();
	//	t.sideMove(b, 1);
	//	clock.addMiliSeconds(200);
	//}
	//t.erase();
	//Tetromino y;
	//y.setTetro(0);
	//y.jumpTo(5, 0);
	//y.rotate(b, -1);
	//y.draw();
	//b.draw();
	//while (y.move(b)) {
	//	b.draw();
	//	y.sideMove(b, -1);
	//	clock.addMiliSeconds(200);
	//}
	//y.erase();
	//Tetromino u;
	//u.setTetro(0);
	//u.jumpTo(5, 0);
	//u.rotate(b, 1);
	//u.draw();
	//b.draw();
	//while (u.move(b)) {
	//	b.draw();
	//	clock.addMiliSeconds(200);
	//}
	//u.erase();
	//b.draw();
	//clock.addMiliSeconds(2000);
}
