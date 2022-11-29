#include <iostream>
#include "Board.h"

Board::Board(int k, int l) : x(k), y(l) {
	int i;
	a = new Block * [k];
	for (i = 0; i < k; i++)
		a[i] = new Block[l];
}

Board::~Board() {
	int i;
	for (i = 0; i < x; i++)
		delete a[i];
	delete a;
}

int Board::getx() {
	return x;
}

int Board::gety() {
	return y;
}