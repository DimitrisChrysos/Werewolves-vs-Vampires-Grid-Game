#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <string>
#include "game.h"

using namespace std;

bool check_player_really_stuck(Board& games_board, Avatar& player) {
	int x = player.get_x();	//player coords
	int y = player.get_y();
	int height = games_board.getx() - 1; //board measurements, (both of the measurements {width, height} start from 0)
	int width = games_board.gety() - 1;
	if (x == 0) {
		if (y == 0) {
			if (games_board.a[x + 1][y].is_accessible_for_avatar() == false &&
				games_board.a[x][y + 1].is_accessible_for_avatar() == false) {

				return true;
			}
		}
		else if (y == width) {
			if (games_board.a[x + 1][y].is_accessible_for_avatar() == false &&
				games_board.a[x][y - 1].is_accessible_for_avatar() == false) {

				return true;
			}
		}
		else {
			if (games_board.a[x + 1][y].is_accessible_for_avatar() == false &&
				games_board.a[x][y + 1].is_accessible_for_avatar() == false &&
				games_board.a[x][y - 1].is_accessible_for_avatar() == false) {

				return true;
			}
		}
	}
	else if (x == height) {
		if (y == 0) {
			if (games_board.a[x - 1][y].is_accessible_for_avatar() == false &&
				games_board.a[x][y + 1].is_accessible_for_avatar() == false) {

				return true;
			}
		}
		else if (y == width) {
			if (games_board.a[x - 1][y].is_accessible_for_avatar() == false &&
				games_board.a[x][y - 1].is_accessible_for_avatar() == false) {

				return true;
			}
		}
		else {
			if (games_board.a[x - 1][y].is_accessible_for_avatar() == false &&
				games_board.a[x][y + 1].is_accessible_for_avatar() == false &&
				games_board.a[x][y - 1].is_accessible_for_avatar() == false) {

				return true;
			}
		}
	}
	else if (y == 0) {
		if (games_board.a[x + 1][y].is_accessible_for_avatar() == false &&
			games_board.a[x - 1][y].is_accessible_for_avatar() == false &&
			games_board.a[x][y + 1].is_accessible_for_avatar() == false) {

			return true;
		}
	}
	else if (y == width) {
		if (games_board.a[x + 1][y].is_accessible_for_avatar() == false &&
			games_board.a[x - 1][y].is_accessible_for_avatar() == false &&
			games_board.a[x][y - 1].is_accessible_for_avatar() == false) {

			return true;
		}
	}
	else if (x != 0 && x != height && y != 0 && y != width) {
		if (games_board.a[x + 1][y].is_accessible_for_avatar() == false &&
			games_board.a[x - 1][y].is_accessible_for_avatar() == false &&
			games_board.a[x][y + 1].is_accessible_for_avatar() == false &&
			games_board.a[x][y - 1].is_accessible_for_avatar() == false) {

			return true;
		}
	}
	return false;
}

int game_input(Board &games_board, Avatar &player, Vampires* v, Werewolves* w) {

	//starts the game
	system("cls");
	cout << "Pause by pressing [p]" << endl << "Exit by pressing [esc]" << endl;
	cout << "Move with the arrows or with [w]-[a]-[s]-[d]" << endl;
	cout << "Heal your team with [q]" << endl;
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

	// player movement counter to change the time
	int move_counter = 0;
	
	bool exit = false;
	while (exit == false) {

		// ends the game
		if (games_board.get_number_of_vam() == 0) {
			if (player.get_team() == 'W') {
				cout << "\n\nCongratulations your team won! There are no Vampires left!\n\n";
				cout << "The game has ended\n";
				exit = true;
				continue;
			}
			else if (player.get_team() == 'V') {
				cout << "\n\nUnfortunately your team lost. Better luck next time! There are no Vampires left!\n\n";
				cout << "The game has ended\n";
				exit = true;
				continue;
			}
		}
		else if (games_board.get_number_of_wer() == 0) {
			if (player.get_team() == 'V') {
				cout << "\n\nCongratulations your team won! There are no Werewolves left!\n\n";
				cout << "The game has ended\n";
				exit = true;
				continue;
			}
			else if (player.get_team() == 'W') {
				cout << "\n\nUnfortunately your team lost. Better luck next time! There are no Werewolves left!\n\n";
				cout << "The game has ended\n";
				exit = true;
				continue;
			}
		}

		// changes games time
		if (move_counter == 8) {
			games_board.change_time();
			move_counter = 0;
		}

		// user input
		this_thread::sleep_for(150ms);
		if (GetKeyState(0x57) & 0x8000 || GetKeyState(VK_UP) & 0x8000) {	// to move up

			system("cls");
			if (player.make_avatar_movement(games_board, player, "up") == 0)
				continue;
			else {
				games_board.make_npc_movement(v, w);
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
				games_board.make_npc_movement(v, w);
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
				games_board.make_npc_movement(v, w);
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
				games_board.make_npc_movement(v, w);
				move_counter++;
				games_board.print();
				continue;
			}
		}
		if (GetKeyState(0x50) & 0x8000) {	// to pause the game

			system("cls");
			cout << "The game is paused\n\n";

			// print number of active vampires, werewolves and magic potions
			cout << "Total number of Werewolves: " << games_board.get_number_of_wer() << endl;
			cout << "Total number of Vampires: " << games_board.get_number_of_vam() << endl;
			cout << "Total number of Magic Potions: " << player.get_magic_potion() << endl;
			cout << endl;

			system("pause");
			system("cls");
			games_board.print();
			continue;
		}
		if (GetKeyState(0x51) & 0x8000) {	// To heal all friendly entities
			int max_x = games_board.getx();
			int max_y = games_board.gety();
			if (player.get_team() == 'W' && games_board.return_time() == 2 && player.get_magic_potion()) {
				for (int i = 0; i < (max_x * max_y / 15); i++) {
					w[i].heal();
				}
				cout << "Your team is healed!\n";
				player.reduce_potions();
			}
			else if (player.get_team() == 'V' && games_board.return_time() == 1 && player.get_magic_potion()) {
				for (int i = 0; i < (max_x * max_y / 15); i++) {
					v[i].heal();
				}
				cout << "Your team is healed!\n";
				player.reduce_potions();
			}
			else if (!player.get_magic_potion()) {
				cout << "You have no magic potions left.\n";
			}
			else if ((player.get_team() == 'V' && games_board.return_time() == 2) ||
				(player.get_team() == 'W' && games_board.return_time() == 1)) {
				cout << "Wrong time for healing. Try again later.\n";
			}
			else continue;
		}
		if (GetKeyState(VK_ESCAPE) & 0x8000) {	// to exit the game

			system("cls");
			cout << "\nThe game has ended\n";
			exit = true;
		}
	}
	return 0;
}