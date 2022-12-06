#include <iostream>
#include "game.h"
#include <cstdlib>
#include <time.h>

using namespace std;

// This is a file exclusively for the function decide() of classes Werewolves and Vampires
// Because the code is really large and very repetitive, we thought it would be better if those functions were written
// in a file of their own.



void Npc::try_heal_or_attack(Board &b, int x, int y) {
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

		srand(time(0));
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
		else if (temp_npc->strength > this->defense) {
			this->avoid(b);
		}
	}
}

void Npc::avoid(Board& b) {

}

void Npc::decide(Board& b) {
	int height = b.getx() - 1; //start from 0
	int width = b.gety() - 1; //start from 0


	if (this->x == 0) {
		if (this->y == 0) {
			this->try_heal_or_attack(b, x + 1, y);
			this->try_heal_or_attack(b, x, y + 1);
		}
		else if (this->y == width) {
			this->try_heal_or_attack(b, x + 1, y);
			this->try_heal_or_attack(b, x, y - 1);
		}
		else {
			this->try_heal_or_attack(b, x + 1, y);
			this->try_heal_or_attack(b, x, y + 1);
			this->try_heal_or_attack(b, x, y - 1);
		}
	}
	else if (this->x == height) {
		if (this->y == 0) {
			this->try_heal_or_attack(b, x - 1, y);
			this->try_heal_or_attack(b, x, y + 1);
		}
		else if (this->y == width) {
			this->try_heal_or_attack(b, x - 1, y);
			this->try_heal_or_attack(b, x, y - 1);
		}
		else {
			this->try_heal_or_attack(b, x - 1, y);
			this->try_heal_or_attack(b, x, y + 1);
			this->try_heal_or_attack(b, x, y - 1);
		}
	}
	else if (this->y == 0) {
		this->try_heal_or_attack(b, x + 1, y);
		this->try_heal_or_attack(b, x - 1, y);
		this->try_heal_or_attack(b, x, y + 1);
	}
	else if (this->y == width) {
		this->try_heal_or_attack(b, x + 1, y);
		this->try_heal_or_attack(b, x - 1, y);
		this->try_heal_or_attack(b, x, y - 1);
	}
	else if (this->x != 0 && this->x != height && this->y != 0 && this->y != width) {
		this->try_heal_or_attack(b, x + 1, y);
		this->try_heal_or_attack(b, x - 1, y);
		this->try_heal_or_attack(b, x, y + 1);
		this->try_heal_or_attack(b, x, y - 1);
	}



	Werewolves* t4;
	Vampires* t5;
	if (team == 'v') {
		t5 = (Vampires*)this;
		t5->gen_move(&b);
	}
	else {
		t4 = (Werewolves*)this;
		t4->gen_move(&b);
	}
}