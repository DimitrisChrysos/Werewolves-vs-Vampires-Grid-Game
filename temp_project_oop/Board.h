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
    void print();
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
};