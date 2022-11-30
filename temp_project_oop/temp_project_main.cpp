#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

#include "game.h"

using namespace std;

int game_input(Board games_board) {
	system("cls");
	cout << "Pause by pressing [p]" << endl << "Exit by pressing [esc]" << endl;
	cout << "Move with the arrows or with [w]-[a]-[s]-[d]" << endl;
	cout << "Ready?\n";
	system("pause");

	
	system("cls");
	
	cout << "1...\n";
	this_thread::sleep_for(500ms);
	cout << "2...\n";
	this_thread::sleep_for(500ms);
	cout << "3...\n";
	this_thread::sleep_for(500ms);
	cout << "Go Go Go!!!\n\n\n";
	this_thread::sleep_for(1s);

	system("cls");
	games_board.print();

	//player movement
	bool exit = false;
	while (exit == false) {

		// print the new board

		this_thread::sleep_for(50ms);
		if (GetKeyState(0x57) & 0x8000 || GetKeyState(VK_UP) & 0x8000) {	// to move up

			system("cls");
			games_board.print();
			continue;
		}
		if (GetKeyState(0x53) & 0x8000 || GetKeyState(VK_DOWN) & 0x8000) {	// to move down

			system("cls");
			games_board.print();
			continue;
		}
		if (GetKeyState(0x44) & 0x8000 || GetKeyState(VK_RIGHT) & 0x8000) {	// to move right

			system("cls");
			games_board.print();
			continue;
		}
		if (GetKeyState(0x41) & 0x8000 || GetKeyState(VK_LEFT) & 0x8000) {	// to move left

			system("cls");
			games_board.print();
			continue;
		}
		if (GetKeyState(0x50) & 0x8000) {	// to pause the game

			system("cls");
			cout << "The game is paused\n";

			// print number of vampires etc...

			system("pause");
			system("cls");
			games_board.print();
			continue;
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000) {	// to exit the game

			system("cls");
			cout << "\nThe game has ended\n";
			exit = true;
		}
	}
	return 0;
}

int main() {
	// insertion and exception handling
	cout << "The game has started!\n";
	cout << "Please provide us with the board size...\n";
	
	int x, y;
	bool temp = true;
	int x_or_y = 0;
	while (temp) {
		cout << "x: ";
		cin >> x;
		cout << "y: ";
		cin >> y;
		try {
			if (x <= 0) {
				throw (x);
				x_or_y = x;
			}
			else if (y <= 0) {
				throw (y);
				x_or_y = y;
			}
			else
				temp = false;
		}
		catch (int x_or_y) {
			cout << "Invalid inputs, please provide accurate x and y values...\n";
		}
	}

	cout << "Now, you may select your side (V for Vampires or W for Werewolves)\n";
	string supporting_team;
	temp = true;
	while (temp) {
		cin >> supporting_team;
		try {
			if (supporting_team == "V" || supporting_team == "W") {
				temp = false;
			}
			else
				throw (supporting_team);
		}
		catch (string supporting_team) {
			cout << "Invalid inputs, please insert V or W...\n";
		}
	}

	
	Board games_board(x, y);
	char team = supporting_team[0];
	Avatar player(team);

	system("pause");
	game_input(games_board);

	games_board.delete_game();
}