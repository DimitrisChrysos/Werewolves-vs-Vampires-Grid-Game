#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <string>
#include "game.h"

using namespace std;

int make_avatar_movement(Board b, Avatar &player, string direction) {	//direction: "up", "down", "right", "left"
	int x = player.get_x();
	int y = player.get_y();
	int width = b.gety();
	int height = b.getx();


	// chech if avatar is stuck
	if (x == 0) {
		if (y == 0 &&
			b.a[x + 1][y].is_accessible() == false &&
			b.a[x][y + 1].is_accessible() == false) {

			cout << "You are stuck, try to move around and wait for your near entities to move...\n";
			return 1;
		}
		else if (y == width - 1 &&
				b.a[x + 1][y].is_accessible() == false &&
				b.a[x][y - 1].is_accessible() == false) {

				cout << "You are stuck, try to move around and wait for your near entities to move...\n";
				return 1;
		}
		else if (b.a[x + 1][y].is_accessible() == false &&
				b.a[x][y - 1].is_accessible() == false &&
				b.a[x][y + 1].is_accessible() == false) {

				cout << "You are stuck, try to move around and wait for your near entities to move...\n";
				return 1;
		}
	}
	else if (x == height - 1) {
		if (y == 0 &&
			b.a[x - 1][y].is_accessible() == false &&
			b.a[x][y + 1].is_accessible() == false) {

			cout << "You are stuck, try to move around and wait for your near entities to move...\n";
			return 1;
		}
		else if (y == width - 1 &&
				b.a[x - 1][y].is_accessible() == false &&
				b.a[x][y - 1].is_accessible() == false) {

				cout << "You are stuck, try to move around and wait for your near entities to move...\n";
				return 1;
		}
		else if (b.a[x - 1][y].is_accessible() == false &&
				b.a[x][y - 1].is_accessible() == false &&
				b.a[x][y + 1].is_accessible() == false) {

				cout << "You are stuck, try to move around and wait for your near entities to move...\n";
				return 1;
		}
	}
	else if (y == 0 && 
		b.a[x - 1][y].is_accessible() == false &&
		b.a[x + 1][y].is_accessible() == false &&
		b.a[x][y + 1].is_accessible() == false) {

		cout << "You are stuck, try to move around and wait for your near entities to move...\n";
		return 1;
	}
	else if (y == width - 1 && 
		b.a[x - 1][y].is_accessible() == false &&
		b.a[x + 1][y].is_accessible() == false &&
		b.a[x][y - 1].is_accessible() == false) {

		cout << "You are stuck, try to move around and wait for your near entities to move...\n";
		return 1;
	}
	else if (x != 0 && x != width - 1 && y != 0 && y != height - 1 &&
		b.a[x - 1][y].is_accessible() == false &&
		b.a[x + 1][y].is_accessible() == false &&
		b.a[x][y - 1].is_accessible() == false &&
		b.a[x][y + 1].is_accessible() == false) {
	
		cout << "You are stuck, try to move around and wait for your near entities to move...\n";
		return 1;
	}

	// make the movement if avatar is not stuck
	if (direction == "up") {
		if (x == 0 || b.a[x - 1][y].is_accessible() == false) {
			cout << "Invalid movement, please make another movement...\n";
			b.print();
			return 0;
		}
		else {
			player.move(x - 1, y, b);
		}
	}
	else if (direction == "down") {
		if (x == height - 1 || b.a[x + 1][y].is_accessible() == false) {
			cout << "Invalid movement, please make another movement...\n";
			b.print();
			return 0;
		}
		else {
			player.move(x + 1, y, b);
		}
	}
	else if (direction == "right") {
		if (y == width - 1 || b.a[x][y + 1].is_accessible() == false) {
			cout << "Invalid movement, please make another movement...\n";
			b.print();
			return 0;
		}
		else {
			player.move(x, y + 1, b);
		}
	}
	else if (direction == "left") {
		if (y == 0 || b.a[x][y - 1].is_accessible() == false) {
			cout << "Invalid movement, please make another movement...\n";
			b.print();
			return 0;
		}
		else {
			player.move(x, y - 1, b);
		}
	}
	return 1;
}

int game_input(Board games_board, Avatar &player) {
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
			if (make_avatar_movement(games_board, player, "up") == 0)
				continue;
			else {
				games_board.make_the_moves();
				move_counter++;
				games_board.print();
				continue;
			}
		}
		else if (GetKeyState(0x53) & 0x8000 || GetKeyState(VK_DOWN) & 0x8000) {	// to move down

			system("cls");
			if (make_avatar_movement(games_board, player, "down") == 0)
				continue;
			else {
				games_board.make_the_moves();
				move_counter++;
				games_board.print();
				continue;
			}
		}
		else if (GetKeyState(0x44) & 0x8000 || GetKeyState(VK_RIGHT) & 0x8000) {	// to move right

			system("cls");
			if (make_avatar_movement(games_board, player, "right") == 0)
				continue;
			else {
				games_board.make_the_moves();
				move_counter++;
				games_board.print();
				continue;
			}
		}
		else if (GetKeyState(0x41) & 0x8000 || GetKeyState(VK_LEFT) & 0x8000) {	// to move left

			system("cls");
			if (make_avatar_movement(games_board, player, "left") == 0)
				continue;
			else {
				games_board.make_the_moves();
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