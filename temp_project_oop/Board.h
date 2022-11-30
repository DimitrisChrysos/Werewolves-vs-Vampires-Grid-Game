#pragma once

#include "Entity.h"

class Block;

class Board {
private:
    int x, y; //size
public:
    Block** a;
    Board(int k, int l);
    ~Board();
    int getx();
    int gety();
    void spawn_entities();
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
    
};