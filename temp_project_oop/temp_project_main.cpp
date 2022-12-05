#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <string>
#include "game.h"
#include "game_input.h"

using namespace std;

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
	game_input(games_board, player, v, w, wer);

	games_board.delete_game(v, w);
}