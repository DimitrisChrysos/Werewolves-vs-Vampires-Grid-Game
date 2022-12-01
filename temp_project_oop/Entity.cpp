#include <iostream>
#include <cstdlib>
#include <time.h>
#include "game.h"

/*void Entity::move(int new_x, int new_y, Entity current_Entity) {

}*/

Avatar::Avatar(char t) {
	this->team = t;
	magic_potion = 1;
}

Avatar::~Avatar() {}

char Avatar::get_team() {
	return this->team;
}

Werewolves::Werewolves() {
	srand(time(0));
	health = 3;
	strength = 1 + (rand() % 3);		// strength is randomly generated from 1-3
	defense = 1 + (rand() % 2);			// defense is randomly generated from 1-2
	health_potions = (rand() % 3);		// health potions are randomly generated from 0-2
	alive = true;
	x = y = -1;
	team = 'w';
}

/*void Werewolves::decide(Board b) {
	int max_x = b.getx();
	int max_y = b.gety();
	Entity* temp;
	Werewolves* t;
	Werewolves* t2;
	int num;
	srand(time(0));
	if (x == 0) {
		if (y == 0) {
			if (b.a[x][y + 1].get_id() == 'v') {
				temp = b.a[x][y + 1].get_ent();
				t = (Werewolves*)temp;
				if (strength > t->defense) {
					attack((Npc*)temp, strength-t->defense);
				}
				else if (b.a[x + 1][y].is_accessible()) {
					this->move(x + 1, y, this);
				}
				else if (b.a[x + 1][y].get_id() == 'w') {
					temp = b.a[x + 1][y].get_ent();
					t2 = (Werewolves*)temp;
					num = rand();
					if (num % 2 == 0 && health_potions > 0 && t2->health < 3) {
						health_potions--;
						t2->health++;
					}
				}
			}
		}
	}
}*/

Werewolves::~Werewolves() {}

Vampires::Vampires() {
	srand(time(0));
	health = 3;
	strength = 1 + (rand() % 3);		// strength is randomly generated from 1-3
	defense = 1 + (rand() % 2);			// defense is randomly generated from 1-2
	health_potions = (rand() % 3);		// health potions are randomly generated from 0-2
	alive = true;
	x = y = -1;
	team = 'v';
}

Vampires::~Vampires() {}