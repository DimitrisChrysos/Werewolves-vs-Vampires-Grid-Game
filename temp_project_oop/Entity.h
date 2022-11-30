#pragma once


class Entity {
protected:
	char team;
	int x, y;
public:
	void move(int new_x, int new_y, Entity current_Entity);
};

class Npc : public Entity {
protected:
	int health_potions;
	int health;
	int strength;
	int defense;
	bool alive;
public:

};

class Avatar : public Entity {
	int magic_potion;
public:
	Avatar(char t);
	~Avatar();

};

class Vampires : public Npc {
	//movement functs
public:
	Vampires();
};

class Werewolves : public Npc {
	//movement functs
public:
	Werewolves();
};