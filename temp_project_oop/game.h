#pragma once
#include <string>

class Board;
class Block;

class Entity {
protected:
	char team;
	int x, y;
public:
	void move(int new_x, int new_y, Board &b);  // move an entity
    void change_coords(int a, int b);   // change the old coords to the new ones
};

class Npc : public Entity {
protected:
	int health_potions;
	int health;
	int strength;
	int defense;
	bool alive;
public:
    void heal_attack_avoid(Board& b, int x, int y, char code, int &mov);    // decides whether to heal teamate, attack enemy or avoid the enemy
    void decide(Board &b);  // calls heal_attack_avoid() for the specific location of the npc
    void attack(Npc * n, int damage, Board &b); // attack the enemy
    bool is_alive();    // checks if the npc is alive
    virtual void gen_move(Board* b);    // generates a move for the npc (works with overloading)
    void heal();    // fully heals an npc
    void strength_boost();  // is used to make sure the last npc spawned of each team has the max strength to ensure at least one attack
};

class Avatar : public Entity {
	int magic_potion;
public:
	Avatar(char t);
	~Avatar();
    int get_x();    // returns Avatar's x
    int get_y();    // returns Avatar's y
    int get_magic_potion(); // returns the number of magic potions left
	char get_team();    // returns the team the Avatar supports
    void reduce_potions();  // reduces the Avatars potions by one
    int make_avatar_movement(Board &b, Avatar& player, std::string direction);  // if movement is avaialable, moves the Avatar using the user input {direction: "up", "down", "right", "left"}
};

class Vampires : public Npc {
public:
	Vampires();
    ~Vampires();
    void gen_move(Board * b);   // generates a move for the Vampire
};

class Werewolves : public Npc {
public:
	Werewolves();
    ~Werewolves();
    void gen_move(Board * b);   // generates a move for the Werewolf
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
    int getx(); // returns boards height
    int gety(); // returns boards width
    void spawn_entities(Avatar &player, Vampires * v, Werewolves * w);  // spawns the entities at the board
    void print();   // prints the board (and the time)
    void change_time(); // changes the time
    int return_time();  // returns the time
    int get_number_of_wer();    // returns the number of werewolves left
    int get_number_of_vam();    // returns the number of vampires left
    void reduce_npc(char v_or_w);  // input v or w and it reduces number_of_vampires or number_of_werewolves by 1
    void make_npc_movement(Vampires* v, Werewolves* w); // generates a move for all the vampires and werewolves
    void delete_game(Vampires * v, Werewolves * w); // deletes the game
};

class Block {
private:
    char identity;
    bool accessible;
    Entity* content;
    friend class Board;
public:
    void init(char id); // initializes the block according to the id we give it
    bool is_accessible();  // returns if block is accessible for all the entities
    bool is_accessible_for_avatar();    // returnes if block is accessible for Avatar
    void change_block_id(char id, Entity* cnt); // changes the identity of the block
    Entity* get_ent();  // returns the entity on the block
    char get_id();  // returns the identity(entity team which is on) the block
};