#include "Global.h"
#include <vector>
#include <iostream>

#ifndef MINEFIELD
#define MINEFIELD
using namespace std;

class Minefield {
public:
	//default constructor
	//set each tile to hidden state and without bomb
	Minefield(int row, int col);

	//set one particular pos of the board to be the bomb
	//if successfully set it, return true, else, return false
	bool setBomb(int row, int col);

	//set one particular pos of the board to be another state
	//if successfully set it, return true, else, return false
	bool setState(int row, int col, State s);

	//get the state of a pos on the board (hidden/flag/revealed)
	State get_state(int row, int col);

	//get whether a tile is bomb
	bool get_bomb(int row, int col);

	//number of surrounding bombs
	int surrouded_bombs(int row, int col);

	//get the row of the board
	int get_row();

	//get the column of the board
	int get_col();

	//display the board
	void display();

private:
	class Tile {
	public:
		Tile();
		bool m_hasbomb;
		State m_state;
	};

	int m_row;
	int m_col;
	std::vector<std::vector<Tile>> m_board;
};


#endif // !MINEFIELD

