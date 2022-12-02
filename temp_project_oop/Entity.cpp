#include <iostream>
#include <cstdlib>
#include <time.h>
#include "game.h"

void Entity::move(int new_x, int new_y, Board b) {
	b.a[x][y].change_block_id(' ', NULL);
	x = new_x;
	y = new_y;
	b.a[x][y].change_block_id(team, this);
}

void Npc::attack(Npc* n, int damage) {
	n->health -= damage; // Some other stuff need to be done here as well
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

void Werewolves::gen_move(Board b) {
	bool pos[4];								// Positions are: 0 = up, 1 = down, 2 = right, 3 = left
	int i, max_x = b.getx(), max_y = b.gety();
	srand(time(0));
	int count = 0, j = 0, num, selection = -1;
	for (i = 0; i < 4; i++) pos[i] = false;
	if (x == 0) {
		if (y == 0) {
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
		}
		else if (y == max_y - 1) {
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
		}
		else {
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
		}
	}
	else if (x == max_x - 1) {
		if (y == 0) {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
		}
		else if (y == max_y - 1) {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
		}
		else {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
		}
	}
	else {
		if (y == 0) {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
		}
		else if (y == max_y - 1) {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
		}
		else {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
		}
	}
	for (i = 0; i < 4; i++) {
		if (pos[i]) count++;
	}
	num = (rand() % count);
	for (i = 0; i < 4; i++) {
		if (pos[i]) {
			if (j == num) {
				selection = i;
			}
			else j++;
		}
	}
	switch (selection) {
	case 0:
		move(x - 1, y, b);
		break;
	case 1:
		move(x + 1, y, b);
		break;
	case 2:
		move(x, y + 1, b);
		break;
	case 3:
		move(x, y - 1, b);
		break;
	default:
		return;
	}
}

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

void Vampires::gen_move(Board b) {
	bool pos[8];								// Positions are: 0 = up, 1 = down, 2 = right, 3 = left, 4 = right up, 5 = left up,
	int i, max_x = b.getx(), max_y = b.gety();	// 6 = right down, 7 = left down
	srand(time(0));
	int count = 0, j = 0, num, selection = -1;
	for (i = 0; i < 8; i++) pos[i] = false;
	if (x == 0) {
		if (y == 0) {
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
			if (b.a[x + 1][y + 1].is_accessible()) pos[6] = true;
		}
		else if (y == max_y - 1) {
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
			if (b.a[x + 1][y - 1].is_accessible()) pos[7] = true;
		}
		else {
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
			if (b.a[x + 1][y + 1].is_accessible()) pos[6] = true;
			if (b.a[x + 1][y - 1].is_accessible()) pos[7] = true;
		}
	}
	else if (x == max_x - 1) {
		if (y == 0) {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
			if (b.a[x - 1][y + 1].is_accessible()) pos[4] = true;
		}
		else if (y == max_y - 1) {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
			if (b.a[x - 1][y - 1].is_accessible()) pos[5] = true;
		}
		else {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
			if (b.a[x - 1][y + 1].is_accessible()) pos[4] = true;
			if (b.a[x - 1][y - 1].is_accessible()) pos[5] = true;
		}
	}
	else {
		if (y == 0) {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
			if (b.a[x + 1][y + 1].is_accessible()) pos[6] = true;
			if (b.a[x - 1][y + 1].is_accessible()) pos[4] = true;
		}
		else if (y == max_y - 1) {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
			if (b.a[x + 1][y - 1].is_accessible()) pos[7] = true;
			if (b.a[x - 1][y - 1].is_accessible()) pos[5] = true;
		}
		else {
			if (b.a[x - 1][y].is_accessible()) pos[0] = true;
			if (b.a[x + 1][y].is_accessible()) pos[1] = true;
			if (b.a[x][y + 1].is_accessible()) pos[2] = true;
			if (b.a[x][y - 1].is_accessible()) pos[3] = true;
			if (b.a[x - 1][y + 1].is_accessible()) pos[4] = true;
			if (b.a[x - 1][y - 1].is_accessible()) pos[5] = true;
			if (b.a[x - 1][y + 1].is_accessible()) pos[6] = true;
			if (b.a[x + 1][y + 1].is_accessible()) pos[7] = true;
		}
	}
	for (i = 0; i < 8; i++) {
		if (pos[i]) count++;
	}
	num = (rand() % count);
	for (i = 0; i < 8; i++) {
		if (pos[i]) {
			if (j == num) {
				selection = i;
			}
			else j++;
		}
	}
	switch (selection) {
	case 0:
		move(x - 1, y, b);
		break;
	case 1:
		move(x + 1, y, b);
		break;
	case 2:
		move(x, y + 1, b);
		break;
	case 3:
		move(x, y - 1, b);
		break;
	case 4:
		move(x - 1, y + 1, b);
		break;
	case 5:
		move(x - 1, y - 1, b);
		break;
	case 6:
		move(x + 1, y + 1, b);
		break;
	case 7:
		move(x + 1, y - 1, b);
		break;
	default:
		return;
	}
}

Vampires::~Vampires() {}