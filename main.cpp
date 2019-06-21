
#include <ctime>
#include "Game.h"
#include <stdlib.h>

int main() {

	int row, col, bombs;
	srand(time(0));
	cout << "Please enter the row: ";
	get_int(row);
	while (row < 5 || row > 99) {
		if (row < 0) {
			cout << "Invalid size, try again:";
		}
		else if (row < 5) {
			cout << "It's too small, try again: ";
		}
		else {
			cout << "It's too large, try again: ";
		}
		get_int(row);
	}

	cout << "Please enter the col: ";
	get_int(col);
	while (col < 5 || col > 99) {
		if (col < 0) {
			cout << "Invalid size, try again:";
		}
		else if (col < 5) {
			cout << "It's too small, try again: ";
		}
		else {
			cout << "It's too large, try again: ";
		}
		get_int(col);
	}

	cout << "Please enter the number of bombs: ";
	get_int(bombs);
	while (bombs < row * col / 15 || bombs > row * col) {
		if (bombs < 0) {
			cout << "Invalid size, try again:";
		}
		else if (bombs < row * col / 15) {
			cout << "It's too small, try again: ";
		}
		else {
			cout << "It should not exceed the size of the board, try again:";
		}
		get_int(bombs);
	}
	cout << "\nYou are all set.\n";
	cout << "Press enter to start the game...";
	cin.ignore(10000, '\n');
	system("cls");

	Game g(row, col, bombs);
	g.play();

}
