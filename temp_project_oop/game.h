#pragma once
#include <string>

class Board;
class Block;

class Entity {
protected:
	char team;
	int x, y;
public:
	void move(int new_x, int new_y, Board &b);
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
    void try_heal_or_attack(Board& b, int x, int y);
    void avoid(Board& b);
    void decide(Board &b);
    void attack(Npc * n, int damage, Board &b);
    bool is_alive();
    virtual void gen_move(Board* b);
    void heal();
    void strength_boost();
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
    void reduce_potions();
    int make_avatar_movement(Board &b, Avatar& player, std::string direction);    //direction: "up", "down", "right", "left"
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
    void reduce_npc(char v_or_w);  //input v or w and it reduces number_of_vampires or number_of_werewolves by 1
    void make_npc_movement(Vampires* v, Werewolves* w);
    void delete_game(Vampires * v, Werewolves * w);
};

class Block {
private:
    char identity;
    bool accessible;
    Entity* content;
    friend class Board;
public:
    void init(char id);
    bool is_accessible();  // return true or false
    bool is_accessible_for_avatar();
    void change_block_id(char id, Entity* cnt);
    Entity* get_ent();
    char get_id();
};