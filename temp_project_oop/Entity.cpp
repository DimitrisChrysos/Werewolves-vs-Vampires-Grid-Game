#include <iostream>
#include <cstdlib>
#include <time.h>
#include "game.h"

void Entity::move(int new_x, int new_y, Board &b) {
	b.a[x][y].change_block_id(' ', NULL);
	x = new_x;
	y = new_y;
	b.a[x][y].change_block_id(team, this);
}

void Entity::change_coords(int a, int b) {
	x = a;
	y = b;
}

void Npc::gen_move(Board* b) {}

void Npc::attack(Npc* n, int damage, Board &b) {
	n->health -= damage; // Some other stuff need to be done here as well
	if (n->health <= 0) {
		n->alive = false;
		b.a[n->x][n->y].change_block_id(' ', NULL);
		if (n->team == 'v') {
			b.reduce_npc('v');
		}
		else if (n->team == 'w') {
			b.reduce_npc('w');
		}
	}
}

bool Npc::is_alive() {
	return this->alive;
}

Avatar::Avatar(char t) {
	this->team = t;
	magic_potion = 1;
	x = y = -1;
}

Avatar::~Avatar() {}

int Avatar::get_x() {
	return this->x;
}

int Avatar::get_y() {
	return this->y;
}

int Avatar::get_magic_potion() {
	return this->magic_potion;
}

char Avatar::get_team() {
	return this->team;
}

int Avatar::make_avatar_movement(Board &b, Avatar& player, std::string direction) {	//direction: "up", "down", "right", "left"
	int x = player.get_x();
	int y = player.get_y();
	int width = b.gety();
	int height = b.getx();

	// chech if avatar is stuck
	if (x == 0) {
		if (y == 0 &&
			b.a[x + 1][y].is_accessible_for_avatar() == false &&
			b.a[x][y + 1].is_accessible_for_avatar() == false) {

			std::cout << "You are stuck, try to move around and wait for your near entities to move...\n";
			return 1;
		}
		else if (y == width - 1 &&
			b.a[x + 1][y].is_accessible_for_avatar() == false &&
			b.a[x][y - 1].is_accessible_for_avatar() == false) {

			std::cout << "You are stuck, try to move around and wait for your near entities to move...\n";
			return 1;
		}
		else if (b.a[x + 1][y].is_accessible_for_avatar() == false &&
			b.a[x][y - 1].is_accessible_for_avatar() == false &&
			b.a[x][y + 1].is_accessible_for_avatar() == false) {

			std::cout << "You are stuck, try to move around and wait for your near entities to move...\n";
			return 1;
		}
	}
	else if (x == height - 1) {
		if (y == 0 &&
			b.a[x - 1][y].is_accessible_for_avatar() == false &&
			b.a[x][y + 1].is_accessible_for_avatar() == false) {

			std::cout << "You are stuck, try to move around and wait for your near entities to move...\n";
			return 1;
		}
		else if (y == width - 1 &&
			b.a[x - 1][y].is_accessible_for_avatar() == false &&
			b.a[x][y - 1].is_accessible_for_avatar() == false) {

			std::cout << "You are stuck, try to move around and wait for your near entities to move...\n";
			return 1;
		}
		else if (b.a[x - 1][y].is_accessible_for_avatar() == false &&
			b.a[x][y - 1].is_accessible_for_avatar() == false &&
			b.a[x][y + 1].is_accessible_for_avatar() == false) {

			std::cout << "You are stuck, try to move around and wait for your near entities to move...\n";
			return 1;
		}
	}
	else if (y == 0 &&
		b.a[x - 1][y].is_accessible_for_avatar() == false &&
		b.a[x + 1][y].is_accessible_for_avatar() == false &&
		b.a[x][y + 1].is_accessible_for_avatar() == false) {

		std::cout << "You are stuck, try to move around and wait for your near entities to move...\n";
		return 1;
	}
	else if (y == width - 1 &&
		b.a[x - 1][y].is_accessible_for_avatar() == false &&
		b.a[x + 1][y].is_accessible_for_avatar() == false &&
		b.a[x][y - 1].is_accessible_for_avatar() == false) {

		std::cout << "You are stuck, try to move around and wait for your near entities to move...\n";
		return 1;
	}
	else if (x != 0 && x != width - 1 && y != 0 && y != height - 1 &&
		b.a[x - 1][y].is_accessible_for_avatar() == false &&
		b.a[x + 1][y].is_accessible_for_avatar() == false &&
		b.a[x][y - 1].is_accessible_for_avatar() == false &&
		b.a[x][y + 1].is_accessible_for_avatar() == false) {

		std::cout << "You are stuck, try to move around and wait for your near entities to move...\n";
		return 1;
	}

	// make the movement if avatar is not stuck
	if (direction == "up") {
		if (x == 0 || b.a[x - 1][y].is_accessible_for_avatar() == false) {
			b.print();
			std::cout << std::endl <<"Invalid movement, please make another movement...\n";
			return 0;
		}
		else {
			if (b.a[x - 1][y].get_id() == '+')
				player.magic_potion++;
			player.move(x - 1, y, b);
		}
	}
	else if (direction == "down") {
		if (x == height - 1 || b.a[x + 1][y].is_accessible_for_avatar() == false) {
			b.print();
			std::cout << std::endl << "Invalid movement, please make another movement...\n";
			return 0;
		}
		else {
			if (b.a[x + 1][y].get_id() == '+')
				player.magic_potion++;
			player.move(x + 1, y, b);
		}
	}
	else if (direction == "right") {
		if (y == width - 1 || b.a[x][y + 1].is_accessible_for_avatar() == false) {
			b.print();
			std::cout << std::endl << "Invalid movement, please make another movement...\n";
			return 0;
		}
		else {
			if (b.a[x][y + 1].get_id() == '+')
				player.magic_potion++;
			player.move(x, y + 1, b);
		}
	}
	else if (direction == "left") {
		if (y == 0 || b.a[x][y - 1].is_accessible_for_avatar() == false) {
			b.print();
			std::cout << std::endl << "Invalid movement, please make another movement...\n";
			return 0;
		}
		else {
			if (b.a[x][y - 1].get_id() == '+')
				player.magic_potion++;
			player.move(x, y - 1, b);
		}
	}
	return 1;
	
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

void Werewolves::gen_move(Board * b) {
	bool pos[4];								// Positions are: 0 = up, 1 = down, 2 = right, 3 = left
	int i, max_x = b->getx(), max_y = b->gety();
	srand(time(0));
	int count = 0, j = 0, num, selection = -1;
	for (i = 0; i < 4; i++) pos[i] = false;
	if (x == 0) {
		if (y == 0) {
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
		}
		else if (y == max_y - 1) {
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
		}
		else {
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
		}
	}
	else if (x == max_x - 1) {
		if (y == 0) {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
		}
		else if (y == max_y - 1) {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
		}
		else {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
		}
	}
	else {
		if (y == 0) {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
		}
		else if (y == max_y - 1) {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
		}
		else {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
		}
	}
	for (i = 0; i < 4; i++) {
		if (pos[i]) count++;
	}
	if (!count) return;
	num = (rand() % count);
	for (i = 0; i < 4; i++) {
		if (pos[i]) {
			if (j == num) {
				selection = i;
				break;
			}
			else j++;
		}
	}
	switch (selection) {
	case 0:
		move(x - 1, y, *b);
		break;
	case 1:
		move(x + 1, y, *b);
		break;
	case 2:
		move(x, y + 1, *b);
		break;
	case 3:
		move(x, y - 1, *b);
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

void Vampires::gen_move(Board * b) {
	bool pos[8];								// Positions are: 0 = up, 1 = down, 2 = right, 3 = left, 4 = right up, 5 = left up,
	int i, max_x = b->getx(), max_y = b->gety();	// 6 = right down, 7 = left down
	srand(time(0));
	int count = 0, j = 0, num, selection = -1;
	for (i = 0; i < 8; i++) pos[i] = false;
	if (x == 0) {
		if (y == 0) {
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
			if (b->a[x + 1][y + 1].is_accessible()) pos[6] = true;
		}
		else if (y == max_y - 1) {
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
			if (b->a[x + 1][y - 1].is_accessible()) pos[7] = true;
		}
		else {
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
			if (b->a[x + 1][y + 1].is_accessible()) pos[6] = true;
			if (b->a[x + 1][y - 1].is_accessible()) pos[7] = true;
		}
	}
	else if (x == max_x - 1) {
		if (y == 0) {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
			if (b->a[x - 1][y + 1].is_accessible()) pos[4] = true;
		}
		else if (y == max_y - 1) {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
			if (b->a[x - 1][y - 1].is_accessible()) pos[5] = true;
		}
		else {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
			if (b->a[x - 1][y + 1].is_accessible()) pos[4] = true;
			if (b->a[x - 1][y - 1].is_accessible()) pos[5] = true;
		}
	}
	else {
		if (y == 0) {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
			if (b->a[x + 1][y + 1].is_accessible()) pos[6] = true;
			if (b->a[x - 1][y + 1].is_accessible()) pos[4] = true;
		}
		else if (y == max_y - 1) {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
			if (b->a[x + 1][y - 1].is_accessible()) pos[7] = true;
			if (b->a[x - 1][y - 1].is_accessible()) pos[5] = true;
		}
		else {
			if (b->a[x - 1][y].is_accessible()) pos[0] = true;
			if (b->a[x + 1][y].is_accessible()) pos[1] = true;
			if (b->a[x][y + 1].is_accessible()) pos[2] = true;
			if (b->a[x][y - 1].is_accessible()) pos[3] = true;
			if (b->a[x - 1][y + 1].is_accessible()) pos[4] = true;
			if (b->a[x - 1][y - 1].is_accessible()) pos[5] = true;
			if (b->a[x + 1][y + 1].is_accessible()) pos[6] = true;
			if (b->a[x + 1][y - 1].is_accessible()) pos[7] = true;
		}
	}
	for (i = 0; i < 8; i++) {
		if (pos[i]) count++;
	}
	if (!count) return;
	num = (rand() % count);
	for (i = 0; i < 8; i++) {
		if (pos[i]) {
			if (j == num) {
				selection = i;
				break;
			}
			else j++;
		}
	}
	switch (selection) {
	case 0:
		move(x - 1, y, *b);
		break;
	case 1:
		move(x + 1, y, *b);
		break;
	case 2:
		move(x, y + 1, *b);
		break;
	case 3:
		move(x, y - 1, *b);
		break;
	case 4:
		move(x - 1, y + 1, *b);
		break;
	case 5:
		move(x - 1, y - 1, *b);
		break;
	case 6:
		move(x + 1, y + 1, *b);
		break;
	case 7:
		move(x + 1, y - 1, *b);
		break;
	default:
		return;
	}
}

Vampires::~Vampires() {}