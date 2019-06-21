#include <vector>
#include <utility>

#ifndef GLOBAL
#define GLOBAL

enum State{HIDDEN, FLAG, REVEALED};

//the coordinates of surrounding tiles for a particular tile
std::vector<std::pair<int, int>> surrounding_points(int row, int col, int m_row, int m_col);

void get_row_and_col(int& row, int& col);

void get_int(int& a);

#endif // !GLOBAL

