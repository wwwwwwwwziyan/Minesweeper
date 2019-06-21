#include "Minefield.h"

#ifndef GAME
#define GAME

class Game {
public:
	//default constructor
	Game(int row, int col, int bomb);

	//sweeping the board
	void sweeping(int row, int col);

	//check whether the game has ended,
	//set result to true if win the game, vice versa
	//leave result unchanged if the game has not ended
	void checkStatus(bool& ended, bool& win, int row, int col);

	//a single move
	void move(int& row, int& col);

	//play the game
	void play();

private:
	Minefield m_minefield;

	//total number of grids that are not revealed and are not bombs
	int available_pos;
};
#endif // !GAME

