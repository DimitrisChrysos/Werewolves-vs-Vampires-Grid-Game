#include <iostream>
#include "game.h"
#include <cstdlib>
#include <time.h>

using namespace std;

// This is a file for the function decide() and all related functions of classes Werewolves and Vampires
// Because the code is really large and very repetitive, we thought it would be better if those functions were written
// in a file of their own.



void Npc::heal_attack_avoid(Board &b, int x, int y, char code, int &mov) {
	char at;
	if (this->team == 'v')
		at = 'w';
	else if (this->team == 'w')
		at = 'v';

	Entity* temp;
	temp = b.a[x][y].get_ent();

	Npc* temp_npc;
	temp_npc = (Npc*)temp;

	if (this->team == b.a[x][y].get_id() && this != temp_npc) {		//  if entity is a friendly npc
		int num = rand();

		if (num % 2 == 0 && this->health_potions > 0 && temp_npc->health < 3) {
			this->health_potions--;			// heal it with 50% chance
			temp_npc->health++;
		}
	}
	else if (at == b.a[x][y].get_id()) {	// if entity is an enemy npc
		if (this->strength >= temp_npc->strength) {
			this->attack(temp_npc, this->strength - temp_npc->defense, b);	// attack it
		}
		else if (temp_npc->strength > this->strength && !mov) {		// else try to avoid it ('u' = up, 'd' = down, 'r' = right, 'l' = left)
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
	int height = b.getx() - 1;	// board measurements, (both of the measurements {width, height} start from 0)
	int width = b.gety() - 1;
	int mov = 0;	// this declares whether the entitie has already tried avoiding opponent
	int k = x;	// stores the starting x
	int l = y;	// stores the starting y

	if (k == 0) {
		if (l == 0) {
			this->heal_attack_avoid(b, k + 1, l, 'r', mov);
			this->heal_attack_avoid(b, k, l + 1, 'd', mov);
		}
		else if (l == width) {
			this->heal_attack_avoid(b, k + 1, l, 'l', mov);
			this->heal_attack_avoid(b, k, l - 1, 'd', mov);
		}
		else {
			this->heal_attack_avoid(b, k + 1, l, ' ', mov);
			this->heal_attack_avoid(b, k, l + 1, 'l', mov);
			this->heal_attack_avoid(b, k, l - 1, 'r', mov);
		}
	}
	else if (k == height) {
		if (l == 0) {
			this->heal_attack_avoid(b, k - 1, l, 'r', mov);
			this->heal_attack_avoid(b, k, l + 1, 'u', mov);
		}
		else if (l == width) {
			this->heal_attack_avoid(b, k - 1, l, 'l', mov);
			this->heal_attack_avoid(b, k, l - 1, 'u', mov);
		}
		else {
			this->heal_attack_avoid(b, k - 1, l, ' ', mov);
			this->heal_attack_avoid(b, k, l + 1, 'l', mov);
			this->heal_attack_avoid(b, k, l - 1, 'r', mov);
		}
	}
	else if (l == 0) {
		this->heal_attack_avoid(b, k + 1, l, 'u', mov);
		this->heal_attack_avoid(b, k - 1, l, 'd', mov);
		this->heal_attack_avoid(b, k, l + 1, ' ', mov);
	}
	else if (l == width) {
		this->heal_attack_avoid(b, k + 1, l, 'u', mov);
		this->heal_attack_avoid(b, k - 1, l, 'd', mov);
		this->heal_attack_avoid(b, k, l - 1, ' ', mov);
	}
	else if (k != 0 && k != height && l != 0 && l != width) {
		this->heal_attack_avoid(b, k + 1, l, 'u', mov);
		this->heal_attack_avoid(b, k - 1, l, 'd', mov);
		this->heal_attack_avoid(b, k, l + 1, 'l', mov);
		this->heal_attack_avoid(b, k, l - 1, 'r', mov);
	}

	if (!mov)	// if the entity has not made a move, generate one
		this->gen_move(&b);
}