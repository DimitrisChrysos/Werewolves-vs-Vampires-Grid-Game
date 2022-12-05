#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <string>
#include "game.h"

using namespace std;

int game_input(Board games_board, Avatar &player, Vampires* v, Werewolves* w, int number_of_wer_and_vamp) {
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

		this_thread::sleep_for(150ms);
		if (GetKeyState(0x57) & 0x8000 || GetKeyState(VK_UP) & 0x8000) {	// to move up

			system("cls");
			if (player.make_avatar_movement(games_board, player, "up") == 0)
				continue;
			else {
				games_board.make_entities_movement(v, w, number_of_wer_and_vamp);
				move_counter++;
				games_board.print();
				continue;
			}
		}
		else if (GetKeyState(0x53) & 0x8000 || GetKeyState(VK_DOWN) & 0x8000) {	// to move down

			system("cls");
			if (player.make_avatar_movement(games_board, player, "down") == 0)
				continue;
			else {
				games_board.make_entities_movement(v, w, number_of_wer_and_vamp);
				move_counter++;
				games_board.print();
				continue;
			}
		}
		else if (GetKeyState(0x44) & 0x8000 || GetKeyState(VK_RIGHT) & 0x8000) {	// to move right

			system("cls");
			if (player.make_avatar_movement(games_board, player, "right") == 0)
				continue;
			else {
				games_board.make_entities_movement(v, w, number_of_wer_and_vamp);
				move_counter++;
				games_board.print();
				continue;
			}
		}
		else if (GetKeyState(0x41) & 0x8000 || GetKeyState(VK_LEFT) & 0x8000) {	// to move left

			system("cls");
			if (player.make_avatar_movement(games_board, player, "left") == 0)
				continue;
			else {
				games_board.make_entities_movement(v, w, number_of_wer_and_vamp);
				move_counter++;
				games_board.print();
				continue;
			}
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