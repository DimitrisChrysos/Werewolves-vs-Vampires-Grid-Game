#pragma once

class Board;
class Block;

class Entity {
protected:
	char team;
	int x, y;
public:
	/*virtual*/ void move(int new_x, int new_y, Entity * current_Entity);
};

class Npc : public Entity {
protected:
	int health_potions;
	int health;
	int strength;
	int defense;
	bool alive;
public:
    /*void move(int new_x, int new_y, Npc* current_Npc);
    virtual void decide(Board b);
    virtual void attack(Npc * n, int damage);*/
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
    /*void move(int new_x, int new_y, Vampires* current_Vam);
    void decide(Board b);
    void attack(Npc * n, int damage);*/
};

class Werewolves : public Npc {
	//movement functs
public:
	Werewolves();
    ~Werewolves();
    /*void move(int new_x, int new_y, Werewolves* current_Wer);
    void decide(Board b);
    void attack(Npc* n, int damage);*/
};


class Board {
private:
    int x, y; //size
public:
    Block** a;
    Board(int k, int l);
    ~Board();
    int getx();
    int gety();
    void spawn_entities(Avatar player);
    void print();
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