#include "Global.h"
#include <iostream>
using namespace std;

vector<pair<int, int>> surrounding_points(int row, int col, int m_row, int m_col)
{
	vector<pair<int, int>> vec;

	int up_row = row - 1;
	if (up_row < 0) { //if up row is not defined
		up_row++;
	}

	int down_row = row + 1;
	if (down_row >= m_row) { //if down row is not defined
		down_row--;
	}

	int left_col = col - 1;
	if (left_col < 0) { //if left col is not defined
		left_col++;
	}

	int right_col = col + 1;
	if (right_col >= m_col) { //if left row is not defined
		right_col--;
	}

	for (int i = up_row; i <= down_row; i++) {
		for (int j = left_col; j <= right_col; j++) {
			if (!(i == row && j == col)) {
				vec.push_back(make_pair(i, j));
			}
		}
	}

	return vec;
}

void get_row_and_col(int & row, int & col)
{
	cin >> row;

	if (cin.fail()) {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		row = -1;
	}

	cin >> col;
	if (cin.fail()) {
		cin.clear();
		cin.sync();
		col = -1;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void get_int(int & a)
{
	cin >> a;

	if (cin.fail()) {
		cin.clear();
		cin.sync();
		a = -1;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
