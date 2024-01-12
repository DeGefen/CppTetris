#include <Windows.h>
#include "MasterHeader.h"
#include "Tetromino.h"
using namespace std;

int main() {
	Board b;
	Tetromino t;
	for (int j = 0; j < 7; j++)
	{

		t.setTetro(j);
		t.jumpTo(4, 5);
		t.draw();
		for (int i = 0; i < 10; i++)
		{
			Sleep(300);
			t.rotate(b, 1);
		}
		Sleep(300);
		t.erase();
	}
}
