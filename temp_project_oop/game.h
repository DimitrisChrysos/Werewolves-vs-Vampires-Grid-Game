#pragma once
#include <string>

class Board;
class Block;

class Entity {
protected:
	char team;
	int x, y;
public:
	void move(int new_x, int new_y, Board b);
    void change_coords(int a, int b);
};

class Npc : public Entity {
protected:
	int health_potions;
	int health;
	int strength;
	int defense;
	bool alive;
public:
    void decide(Board b);
    void attack(Npc * n, int damage, Board b);
    bool is_alive();
    virtual void gen_move(Board * b) {}
};

class Avatar : public Entity {
	int magic_potion;
public:
	Avatar(char t);
	~Avatar();
    int get_x();
    int get_y();
    int get_magic_potion();
	char get_team();
    int make_avatar_movement(Board b, Avatar& player, std::string direction);    //direction: "up", "down", "right", "left"
};

class Vampires : public Npc {
	//movement functs
public:
	Vampires();
    ~Vampires();
    void gen_move(Board * b);
};

class Werewolves : public Npc {
	//movement functs
public:
	Werewolves();
    ~Werewolves();
    void gen_move(Board * b);
};


class Board {
private:
    int x, y; //size
    int day_or_night;    // day -> [1] or night -> [2]
    int number_of_werewolves;
    int number_of_vampires;
public:
    Block** a;
    Board(int k, int l, int number_of_wer, int number_of_vam);
    ~Board();
    int getx();
    int gety();
    void spawn_entities(Avatar &player, Vampires * v, Werewolves * w);
    void print();
    void change_time();
    int return_time();
    int get_number_of_wer();
    int get_number_of_vam();
    void make_npc_movement(Vampires* v, Werewolves* w);
    void delete_game(Vampires * v, Werewolves * w);
};

class Block {
private:
    int x, y;  //coords
    char identity;
    bool accessible;
    Entity* content;
    friend class Board;
public:
    void init(int a, int b, char id);
    int is_accessible();  // return true or false
    void change_block_id(char id, Entity* cnt);
    Entity* get_ent();
    char get_id();
};