#include <iostream>
#include "game.h"
#include <cstdlib>
#include <time.h>

using namespace std;

// This is a file exclusively for the function decide() of classes Werewolves and Vampires
// Because the code is really large and very repetitive, we thought it would be better if those functions were written
// in a file of their own.



void Npc::heal_attack_avoid(Board &b, int x, int y, char code, int &mov) {
	char anti_team;
	if (this->team == 'v')
		anti_team = 'w';
	else if (this->team == 'w')
		anti_team = 'v';

	Entity* temp;
	temp = b.a[x][y].get_ent();

	Npc* temp_npc;
	temp_npc = (Npc*)temp;

	srand(time(0));

	if (this->team == b.a[x][y].get_id()) {
		Entity* temp;
		temp = b.a[x][y].get_ent();

		Npc* temp_npc;
		temp_npc = (Npc*)temp;

		int num = rand();

		if (num % 2 == 0 && this->health_potions > 0 && temp_npc->health < 3) {
			this->health_potions--;
			temp_npc->health++;
		}
	}
	else if (anti_team == b.a[x][y].get_id()) {
		if (this->strength > temp_npc->defense) {
			this->attack(temp_npc, this->strength - temp_npc->defense, b);
		}
		else if (temp_npc->strength > this->defense && !mov) {
			if (code == 'u') {
				if (b.a[x - 1][y].is_accessible()) {
					this->move(x - 1, y, b);
					mov = 1;
				}
			}
			else if (code == 'd') {
				if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, b);
					mov = 1;
				}
			}
			else if (code == 'r') {
				if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, b);
					mov = 1;
				}
			}
			if (code == 'l') {
				if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, b);
					mov = 1;
				}
			}
		}
	}
}

void Npc::decide(Board& b) {
	int height = b.getx() - 1; //start from 0
	int width = b.gety() - 1; //start from 0
	int mov = 0;


	if (this->x == 0) {
		if (this->y == 0) {
			this->heal_attack_avoid(b, x + 1, y, 'r', mov);
			this->heal_attack_avoid(b, x, y + 1, 'd', mov);
		}
		else if (this->y == width) {
			this->heal_attack_avoid(b, x + 1, y, 'l', mov);
			this->heal_attack_avoid(b, x, y - 1, 'd', mov);
		}
		else {
			this->heal_attack_avoid(b, x + 1, y, ' ', mov);
			this->heal_attack_avoid(b, x, y + 1, 'l', mov);
			this->heal_attack_avoid(b, x, y - 1, 'r', mov);
		}
	}
	else if (this->x == height) {
		if (this->y == 0) {
			this->heal_attack_avoid(b, x - 1, y, 'r', mov);
			this->heal_attack_avoid(b, x, y + 1, 'u', mov);
		}
		else if (this->y == width) {
			this->heal_attack_avoid(b, x - 1, y, 'l', mov);
			this->heal_attack_avoid(b, x, y - 1, 'u', mov);
		}
		else {
			this->heal_attack_avoid(b, x - 1, y, ' ', mov);
			this->heal_attack_avoid(b, x, y + 1, 'l', mov);
			this->heal_attack_avoid(b, x, y - 1, 'r', mov);
		}
	}
	else if (this->y == 0) {
		this->heal_attack_avoid(b, x + 1, y, 'u', mov);
		this->heal_attack_avoid(b, x - 1, y, 'd', mov);
		this->heal_attack_avoid(b, x, y + 1, ' ', mov);
	}
	else if (this->y == width) {
		this->heal_attack_avoid(b, x + 1, y, 'u', mov);
		this->heal_attack_avoid(b, x - 1, y, 'd', mov);
		this->heal_attack_avoid(b, x, y - 1, ' ', mov);
	}
	else if (this->x != 0 && this->x != height && this->y != 0 && this->y != width) {
		this->heal_attack_avoid(b, x + 1, y, 'u', mov);
		this->heal_attack_avoid(b, x - 1, y, 'd', mov);
		this->heal_attack_avoid(b, x, y + 1, 'l', mov);
		this->heal_attack_avoid(b, x, y - 1, 'r', mov);
	}

	if (!mov)
		this->gen_move(&b);
}