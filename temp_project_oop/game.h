#pragma once

class Board;
class Block;

class Entity {
protected:
	char team;
	int x, y;
public:
	void move(int new_x, int new_y, Board b);
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
    void attack(Npc * n, int damage);
    bool is_alive();
    virtual void gen_move(Board * b) {}
};

class Avatar : public Entity {
	int magic_potion;
public:
	Avatar(char t);
	~Avatar();
	char get_team();
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
public:
    Block** a;
    Board(int k, int l);
    ~Board();
    int getx();
    int gety();
    void spawn_entities(Avatar player);
    void print();
    void change_time();
    int return_time();
    void make_the_moves();
    void delete_game();
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
    int is_accessible();  // return 1 if true - 0 if not true
    void change_block_id(char id, Entity* cnt);
    Entity* get_ent();
    char get_id();
};