#pragma once

#include "Entity.h"

class Block;

class Board {
private:
	int x, y; //size
public:
	Block **a;
	Board(int k, int l);
	~Board();
	int getx();
	int gety();
};

class Block {
private:
	int x, y;  //coords
	char identity;
	bool accessible;
	Entity* content;
	
};