#include <Windows.h>
#include "MasterHeader.h"
#include "Tetromino.h"
using namespace std;

int main() {
	Board b;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	cout << b.count() << endl;
	Tetromino t;
	t.setTetro(5);
	t.jumpTo(5, 0);
	t.draw();
	while (t.move(b)) {
		t.sideMove(b, 1);
	cout << b.count() << endl;
	Sleep(250);
	}
	
	t.erase();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	cout << b.count() << endl;
	//Point p;
	//p.init(1, 1);
	//p.draw('J');
}
