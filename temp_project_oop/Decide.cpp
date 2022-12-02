#include <iostream>
#include "game.h"
#include <cstdlib>
#include <time.h>

using namespace std;

// This is a file exclusively for the functions decide() of classes Werewolves and Vampires
// Because the code is really large and very repetitive, we thought it would be better if those functions were written
// in a file of their own.

/*void Werewolves::decide(Board b) {
	int max_x = b.getx();
	int max_y = b.gety();
	Entity* temp;
	Werewolves* t;
	Werewolves* t2;
	int num;
	srand(time(0));
	if (x == 0) {
		if (b.a[x + 1][y].get_id() == 'w') {
			temp = b.a[x + 1][y].get_ent();
			t2 = (Werewolves*)temp;
			num = rand();
			if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
				health_potions--;
				t2->health++;
			}
		}
		if (y == 0) {
			if (b.a[x][y + 1].get_id() == 'w') {
				temp = b.a[x][y + 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y + 1].get_id() == 'v') {
				temp = b.a[x][y + 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, this);
				}
			}
			else if (b.a[x + 1][y].get_id() == 'v') {
				temp = b.a[x + 1][y].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, this);
				}
			}
			else if (b.a[x + 1][y].is_accessible() && b.a[x][y + 1].is_accessible()) {
				num = rand();
				if (num % 2 == 0) this->move(x + 1, y, this);
				else this->move(x, y + 1, this);
			}
			else if (b.a[x + 1][y].is_accessible()) {
				this->move(x + 1, y, this);
			}
			else if (b.a[x][y + 1].is_accessible()) {
				this->move(x, y + 1, this);
			}
		}
		else if (y == max_y - 1) {
			if (b.a[x][y - 1].get_id() == 'w') {
				temp = b.a[x][y - 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y - 1].get_id() == 'v') {
				temp = b.a[x][y - 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, this);
				}
			}
			else if (b.a[x + 1][y].get_id() == 'v') {
				temp = b.a[x + 1][y].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, this);
				}
			}
			else if (b.a[x + 1][y].is_accessible()) {
				this->move(x + 1, y, this);
			}
			else if (b.a[x][y - 1].is_accessible()) {
				this->move(x, y - 1, this);
			}
		}
		else {
			if (b.a[x][y + 1].get_id() == 'w') {
				temp = b.a[x][y + 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y - 1].get_id() == 'w') {
				temp = b.a[x][y - 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y + 1].get_id() == 'v') {
				temp = b.a[x][y + 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, this);
				}
				else if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, this);
				}
			}
			else if (b.a[x + 1][y].get_id() == 'v') {
				temp = b.a[x + 1][y].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, this);
				}
				else if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, this);
				}
			}
			else if (b.a[x][y - 1].get_id() == 'v') {
				temp = b.a[x][y - 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, this);
				}
				else if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, this);
				}
			}
			else if (b.a[x + 1][y].is_accessible()) {
				this->move(x + 1, y, this);
			}
			else if (b.a[x][y - 1].is_accessible()) {
				this->move(x, y - 1, this);
			}
			else if (b.a[x][y + 1].is_accessible()) {
				this->move(x, y + 1, this);
			}
		}
	}
	else if (x == max_x - 1) {
		if (b.a[x - 1][y].get_id() == 'w') {
			temp = b.a[x - 1][y].get_ent();
			t2 = (Werewolves*)temp;
			num = rand();
			if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
				health_potions--;
				t2->health++;
			}
		}
		if (y == 0) {
			if (b.a[x][y + 1].get_id() == 'w') {
				temp = b.a[x][y + 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y + 1].get_id() == 'v') {
				temp = b.a[x][y + 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x - 1][y].is_accessible()) {
					this->move(x - 1, y, this);
				}
			}
			else if (b.a[x - 1][y].get_id() == 'v') {
				temp = b.a[x - 1][y].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, this);
				}
			}
			else if (b.a[x - 1][y].is_accessible()) {
				this->move(x - 1, y, this);
			}
			else if (b.a[x][y + 1].is_accessible()) {
				this->move(x, y + 1, this);
			}
		}
		else if (y == max_y - 1) {
			if (b.a[x][y - 1].get_id() == 'w') {
				temp = b.a[x][y - 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y - 1].get_id() == 'v') {
				temp = b.a[x][y - 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x - 1][y].is_accessible()) {
					this->move(x - 1, y, this);
				}
			}
			else if (b.a[x - 1][y].get_id() == 'v') {
				temp = b.a[x - 1][y].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, this);
				}
			}
			else if (b.a[x - 1][y].is_accessible()) {
				this->move(x - 1, y, this);
			}
			else if (b.a[x][y - 1].is_accessible()) {
				this->move(x, y - 1, this);
			}
		}
		else {
			if (b.a[x][y + 1].get_id() == 'w') {
				temp = b.a[x][y + 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y - 1].get_id() == 'w') {
				temp = b.a[x][y - 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y + 1].get_id() == 'v') {
				temp = b.a[x][y + 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, this);
				}
				else if (b.a[x - 1][y].is_accessible()) {
					this->move(x - 1, y, this);
				}
			}
			else if (b.a[x - 1][y].get_id() == 'v') {
				temp = b.a[x - 1][y].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, this);
				}
				else if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, this);
				}
			}
			else if (b.a[x][y - 1].get_id() == 'v') {
				temp = b.a[x][y - 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, this);
				}
				else if (b.a[x - 1][y].is_accessible()) {
					this->move(x - 1, y, this);
				}
			}
			else if (b.a[x - 1][y].is_accessible()) {
				this->move(x - 1, y, this);
			}
			else if (b.a[x][y - 1].is_accessible()) {
				this->move(x, y - 1, this);
			}
			else if (b.a[x][y + 1].is_accessible()) {
				this->move(x, y + 1, this);
			}
		}
	}
	else {
		if (b.a[x + 1][y].get_id() == 'w') {
			temp = b.a[x + 1][y].get_ent();
			t2 = (Werewolves*)temp;
			num = rand();
			if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
				health_potions--;
				t2->health++;
			}
		}
		if (b.a[x - 1][y].get_id() == 'w') {
			temp = b.a[x - 1][y].get_ent();
			t2 = (Werewolves*)temp;
			num = rand();
			if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
				health_potions--;
				t2->health++;
			}
		}
		if (y == 0) {
			if (b.a[x][y + 1].get_id() == 'w') {
				temp = b.a[x][y + 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y + 1].get_id() == 'v') {
				temp = b.a[x][y + 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, this);
				}
			}
			else if (b.a[x + 1][y].get_id() == 'v') {
				temp = b.a[x + 1][y].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, this);
				}
			}
			else if (b.a[x + 1][y].is_accessible()) {
				this->move(x + 1, y, this);
			}
			else if (b.a[x][y + 1].is_accessible()) {
				this->move(x, y + 1, this);
			}
		}
		else if (y == max_y - 1) {
			if (b.a[x][y - 1].get_id() == 'w') {
				temp = b.a[x][y - 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y - 1].get_id() == 'v') {
				temp = b.a[x][y - 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, this);
				}
			}
			else if (b.a[x + 1][y].get_id() == 'v') {
				temp = b.a[x + 1][y].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, this);
				}
			}
			else if (b.a[x + 1][y].is_accessible()) {
				this->move(x + 1, y, this);
			}
			else if (b.a[x][y - 1].is_accessible()) {
				this->move(x, y - 1, this);
			}
		}
		else {
			if (b.a[x][y + 1].get_id() == 'w') {
				temp = b.a[x][y + 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y - 1].get_id() == 'w') {
				temp = b.a[x][y - 1].get_ent();
				t2 = (Werewolves*)temp;
				num = rand();
				if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
					health_potions--;
					t2->health++;
				}
			}
			if (b.a[x][y + 1].get_id() == 'v') {
				temp = b.a[x][y + 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, this);
				}
				else if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, this);
				}
			}
			else if (b.a[x + 1][y].get_id() == 'v') {
				temp = b.a[x + 1][y].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, this);
				}
				else if (b.a[x][y - 1].is_accessible()) {
					this->move(x, y - 1, this);
				}
			}
			else if (b.a[x][y - 1].get_id() == 'v') {
				temp = b.a[x][y - 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x][y + 1].is_accessible()) {
					this->move(x, y + 1, this);
				}
				else if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, this);
				}
			}
			else if (b.a[x + 1][y].is_accessible()) {
				this->move(x + 1, y, this);
			}
			else if (b.a[x][y - 1].is_accessible()) {
				this->move(x, y - 1, this);
			}
			else if (b.a[x][y + 1].is_accessible()) {
				this->move(x, y + 1, this);
			}
		}
	}
}*/