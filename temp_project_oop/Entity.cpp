#include <iostream>
#include "Entity.h"
#include "Board.h"

void Entity::move(int new_x, int new_y, Entity current_Entity) {

}

Avatar::Avatar(char t) {
	this->team = t;
	magic_potion = 1;
}

Avatar::~Avatar() {}

