#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <string>
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
	int move_counter = 0;
	bool exit = false;
	while (exit == false) {

		
		if (move_counter == 8) {
			games_board.change_time();
			move_counter = 0;
		}

		this_thread::sleep_for(100ms);
		if (GetKeyState(0x57) & 0x8000 || GetKeyState(VK_UP) & 0x8000) {	// to move up

			system("cls");
			games_board.print();
			move_counter++;
			games_board.make_the_moves();
			continue;
		}
		else if (GetKeyState(0x53) & 0x8000 || GetKeyState(VK_DOWN) & 0x8000) {	// to move down

			system("cls");
			games_board.print();
			move_counter++;
			games_board.make_the_moves();
			continue;
		}
		else if (GetKeyState(0x44) & 0x8000 || GetKeyState(VK_RIGHT) & 0x8000) {	// to move right

			system("cls");
			games_board.print();
			move_counter++;
			games_board.make_the_moves();
			continue;
		}
		else if (GetKeyState(0x41) & 0x8000 || GetKeyState(VK_LEFT) & 0x8000) {	// to move left

			system("cls");
			games_board.print();
			move_counter++;
			games_board.make_the_moves();
			continue;
		}
		if (GetKeyState(0x50) & 0x8000) {	// to pause the game

			system("cls");
			cout << "The game is paused\n";

			// print number of vampires etc...
			string current_time;
			if (games_board.return_time() == 1)		//day
				current_time = "day";
			else									//night
				current_time = "night";
			cout << "Current time: " << current_time << endl;

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
			if (x <= 1) {
				throw (x);
				x_or_y = x;
			}
			else if (y <= 1) {
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
	int wer, vam;
	wer = vam = x * y / 15;
	Avatar player(team);
	Vampires* v = new Vampires[vam];
	Werewolves* w = new Werewolves[wer];
	games_board.spawn_entities(player, v, w);

	system("pause");
	game_input(games_board);

	games_board.delete_game(v, w);
}