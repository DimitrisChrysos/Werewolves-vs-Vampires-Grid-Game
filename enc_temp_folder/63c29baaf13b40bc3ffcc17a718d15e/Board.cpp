#include <iostream>
#include "Board.h"
#include <cstdlib>
#include <time.h>

using namespace std;

Board::Board(int k, int l) : x(k), y(l) {
    int i, j, num;
    char sym;
    a = new Block * [k];
    srand(time(0));
    for (i = 0; i < k; i++) {
        a[i] = new Block[l];
        for (j = 0; j < l; j++) {
            num = 1 + (rand() % 100);
            if (num >= 1 && num <= 8) sym = '*';
            else if (num <= 16) sym = '~';
            else sym = ' ';
            a[i][j].init(i, j, sym);
        }
    }
}

Board::~Board() {
    int i;
    cout << "destructor activated\n";
    for (i = 0; i < x; i++)
        delete[] a[i];
    delete[] a;
    cout << "testtt\n";
}

int Board::getx() {
    return x;
}

int Board::gety() {
    return y;
}

void Board::print() {
    int i, j;
    for (i = 0; i < x; i++) {
        cout << endl;
        for (j = 0; j < y; j++) {
            cout << a[i][j].identity;
        }
    }
}

void Block::init(int a, int b, char id) {
    x = a; y = b; identity = id;
    if (id == '*' || id == '~') {
        accessible = false;
    }
    else accessible = true;
    content = NULL;
}