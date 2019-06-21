#include "Minefield.h"
#include <exception>
#include <string>
#include <iomanip>
using namespace std;

Minefield::Minefield(int row, int col)
{
	if (row <= 0 || col <= 0) {
		throw logic_error("row and col must be positive");
	}

	m_row = row;
	m_col = col;
	m_board = vector<vector<Tile>>(row, vector<Tile>(col));
}

bool Minefield::setBomb(int row, int col)
{
	//if out of range
	if (row >= m_row || col >= m_col || row < 0 || col < 0) {
		return false;
	}

	m_board[row][col].m_hasbomb = true;
	return true;
}

bool Minefield::setState(int row, int col, State s)
{
	//if out of range
	if (row >= m_row || col >= m_col || row < 0 || col < 0) {
		return false;
	}

	m_board[row][col].m_state = s;
	return true;
}

State Minefield::get_state(int row, int col)
{
	//if out of range
	if (row >= m_row || col >= m_col) {
		throw logic_error("out of range, try to access " + to_string(row) + "," + to_string(col));
	}

	return	m_board[row][col].m_state;
}

bool Minefield::get_bomb(int row, int col)
{
	//if out of range
	if (row >= m_row || col >= m_col) {
		throw logic_error("out of range, try to access " + to_string(row) + "," + to_string(col));
	}

	return	m_board[row][col].m_hasbomb;
}

int Minefield::surrouded_bombs(int row, int col)
{
	auto coords = surrounding_points(row, col, m_row, m_col);

	int sum = 0;
	for (auto tile : coords) {
		if (m_board[tile.first][tile.second].m_hasbomb == true) {
			sum++;
		}
	}

	return sum;
}

int Minefield::get_row()
{
	return m_row;
}

int Minefield::get_col()
{
	return m_col;
}

void Minefield::display()
{
	cout << "    ";
	for (int col = 0; col <= (m_col - 1) / 10; col++) {
		cout << col << "                   ";
	}
	cout << '\n';


	cout << "    ";
	for (int col = 0; col < m_col; col++) {
		cout << col % 10 << ' ';
	}
	cout << '\n';
	
	cout << "   ";
	for (int col = 0; col < m_col; col++) {
		cout << "--";
	}
	cout << '\n';

	for (int row = 0; row < m_row; row++) {
		cout << setw(2)<<left<<row << " " << '|';
		for (int col = 0; col < m_col; col++) {
			State s = m_board[row][col].m_state;
			if (s == HIDDEN) {
				cout << '.' << ' ';
			}
			else if (s == FLAG) {
				cout << 'F' << ' ';
			}

			//if revealed
			else {
				//if bomb
				if (m_board[row][col].m_hasbomb) {
					cout << '*' << ' ';
				}

				//if not bomb
				else {
					int surrounding = surrouded_bombs(row, col);
					if (surrounding == 0) {
						cout << ' ' << ' ';
					}
					else {
						cout << surrounding << ' ';
					}
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

Minefield::Tile::Tile()
{
	m_hasbomb = false;
	m_state = HIDDEN;
}
