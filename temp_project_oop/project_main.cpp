#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <string>
#include "game.h"
#include "game_input.h"

using namespace std;

int main() {
	// insertion and exception handling for board size and team selection
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
			if (x <= 3 || x > 100) {	// x must be higher than 3 for entities to spawn
				throw (x);
				x_or_y = x;
			}
			else if (y <= 3 || y > 100) {	// y must be higher than 3 for entities to spawn
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

	temp = true;
	char team = supporting_team[0];
	int wer, vam;
	wer = vam = x * y / 15;
	while (temp) {								// this while loop is used to avoid the case of the player being stuck
		Board games_board(x, y, wer, vam);		// by trees and water by all directions when spawned 
		Avatar player(team);
		Vampires* v = new Vampires[vam];
		Werewolves* w = new Werewolves[wer];
		games_board.spawn_entities(player, v, w);

		if (check_player_really_stuck(games_board, player) == true) {	// if player stuck delete the previous game
			games_board.delete_game(v, w);								// and make a new one
			continue;
		}
		else {												// else if player not stuck start the game
			system("pause");
			game_input(games_board, player, v, w);			// basically starts the game
			games_board.delete_game(v, w);
			temp = false;
			continue;
		}
	}
}