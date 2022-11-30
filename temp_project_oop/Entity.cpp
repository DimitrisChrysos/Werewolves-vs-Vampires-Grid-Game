#include <iostream>
#include <cstdlib>
#include <time.h>
#include "game.h"

void Entity::move(int new_x, int new_y, Entity current_Entity) {

}

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