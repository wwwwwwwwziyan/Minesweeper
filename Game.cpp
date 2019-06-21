#include "Game.h"
#include <exception>
#include <iostream>
#include <utility>
#include <unordered_set>
#include <stdlib.h>
#include "Global.h"
using namespace std;

Game::Game(int row, int col, int bomb): m_minefield(row, col),available_pos(row * col - bomb)
{
	if (bomb > row * col) {
		throw logic_error("number of bombs is greater than number of grids");
	}

	if (bomb <= 0) {
		throw logic_error("number of bombs must be positive");
	}

	int t_row;
	int t_col;
	for (int i = 0; i < bomb; i++) {
		t_row = rand() % row;
		t_col = rand() % col;

		//if the grid has been already set to bomb
		if (m_minefield.get_bomb(t_row, t_col) == false) {
			m_minefield.setBomb(t_row, t_col);
		}
		else {
			i--;
		}
	}
}

void Game::sweeping(int row, int col)
{
	//if out of range
	if (row >= m_minefield.get_row() || row < 0 || col >= m_minefield.get_col() || col < 0) {
		return;
	}

	//if it is the bomb or flagged/revealed
	if (m_minefield.get_bomb(row, col) == true || m_minefield.get_state(row,col) != HIDDEN) {
		return;
	}

	//reveal that tile
	m_minefield.setState(row, col, REVEALED);

	//reduce the available pos by 1
	available_pos -= 1;

	//calculate the bombs surrounded
	int surrounding = m_minefield.surrouded_bombs(row, col);
	
	//if there is bomb surrounded
	if (surrounding != 0) {
		return;
	}

	//if no bomb surrounded, sweeping the surrounding tile
	else {
		auto collection = surrounding_points(row, col, m_minefield.get_row(), m_minefield.get_col());
		for (auto tiles : collection) {
			sweeping(tiles.first, tiles.second);
		}
	}
}

void Game::checkStatus(bool & ended, bool & win, int row, int col)
{
	if (available_pos == 0) {
		ended = true;
		win = true;
		return;
	}

	auto coords = surrounding_points(row, col, m_minefield.get_row(), m_minefield.get_col());
	coords.push_back(make_pair(row, col));

	//if a bomb is revealed
	for (auto tile : coords) {
		if (m_minefield.get_state(tile.first, tile.second) == REVEALED 
			&& m_minefield.get_bomb(tile.first, tile.second) == true) {
			ended = true;
			win = false;
			return;
		}
	}

	ended = false;
}

void Game::move(int& row, int& col)
{
	char action;
	cout << "Please enter the action you wanna take\n";
	cout << "Press: c/f/a (click /flag /clear all surroundings):";
	cin >> action;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (action != 'c' && action != 'f' && action != 'a') {
		cout << "Invalid action, please enter a valid one:";
		cin >> action;
	}
	
	cout << "Please enter the row and column:";
	get_row_and_col(row, col);

	//if action is c, let user input the coords until it is hidden
	if (action == 'c') {

		//if the index is out of range or revealed or flagged, let the user try again
		while (row >= m_minefield.get_row() || row < 0 || col >= m_minefield.get_col() || col < 0
			|| m_minefield.get_state(row, col) != HIDDEN) {
			cout << "Invalid index, please enter the valid row and column:";
			get_row_and_col(row, col);
		}
	}

	//if action is f, let user input the coords until it is flagged or hidden
	else if (action == 'f') {

		//if the index is out of range or revealed, let the user try again
		while (row >= m_minefield.get_row() || row < 0 || col >= m_minefield.get_col() || col < 0
			|| m_minefield.get_state(row, col) == REVEALED ) {
			cout << "Invalid index, please enter the valid row and column:";
			get_row_and_col(row, col);
		}
	}

	//if action is a, let user input the coords until it is revealed and it has surrounded bombs
	else if (action == 'a') {

		//if the index is out of range or revealed, let the user try again
		while (row >= m_minefield.get_row() || row < 0 || col >= m_minefield.get_col() || col < 0
			|| m_minefield.get_state(row, col) != REVEALED || m_minefield.surrouded_bombs(row,col) == 0) {
			cout << "Invalid index, please enter the valid row and column:";
			get_row_and_col(row, col);
		}
	}



	//if the action is flag
	if (action == 'f') {
		//if it is not flagged
		if (m_minefield.get_state(row, col) == HIDDEN) {
			m_minefield.setState(row, col, FLAG);
		}

		//if it has already been flagged, undo it
		else {
			m_minefield.setState(row, col, HIDDEN);
		}
	}
	else if(action == 'c'){

		//if bomb
		if (m_minefield.get_bomb(row, col) == true) {
			m_minefield.setState(row, col, REVEALED);
			return;
		}
		else {
			sweeping(row, col);
		}
	}

	//clear all surroundings
	else if (action == 'a') {
		auto coords = surrounding_points(row, col, m_minefield.get_row(), m_minefield.get_col());
	
		coords.push_back(make_pair(row, col));

		for (auto tile : coords) {
			//if it is hidden
			if (m_minefield.get_state(tile.first, tile.second) == HIDDEN) {

				//if bomb
				if (m_minefield.get_bomb(tile.first, tile.second) == true) {
					m_minefield.setState(tile.first, tile.second, REVEALED);
					return;
				}
				else {
					sweeping(tile.first, tile.second);
				}
			}
		}
	}

}

void Game::play()
{
	bool ended;
	bool win;
	int row, col;
	m_minefield.display();

	while (true) {
		//let the user choose the action
		move(row, col);

		//clear the screen
		system("cls");

		//display the board
		m_minefield.display();

		checkStatus(ended, win, row, col);

		//if the game has ended
		if (ended) {
			//if win
			if (win) {
				cout << "You win!\n";
			}
			else {
				cout << "You lose!\n";
			}

			break;
		}
	}	

	cout << "Press enter to quit...";
	cin.ignore(10000, '\n');
}
