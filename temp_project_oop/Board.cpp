#include <iostream>
#include "Board.h"
#include <cstdlib>
#include <time.h>
#include "Entity.h"

using namespace std;

Board::Board(int k, int l) : x(k), y(l) {
    int i, j, num, pot = 0;
    char sym;
    a = new Block * [k];
    srand(time(0));
    for (i = 0; i < k; i++) {
        a[i] = new Block[l];
        for (j = 0; j < l; j++) {
            if (i == k - 1 && j == l - 1 && pot == 0) {
                a[i][j].init(i, j, '+');
                continue;
            }
            num = 1 + (rand() % 100);
            if (num >= 1 && num <= 8) sym = '*';
            else if (num <= 16) sym = '~';
            else if (num <= 21 && pot == 0) {
                pot++;
                sym = '+';
            }
            else sym = ' ';
            a[i][j].init(i, j, sym);
        }
    }
}

Board::~Board() {}

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

void Board::delete_game() {
    int i;
    cout << "destructor activated\n";
    for (i = 0; i < y; i++)
        delete[] a[i];
    delete[] a;
    cout << "testtt\n";
}

void Block::init(int a, int b, char id) {
    x = a; y = b; identity = id;
    if (id == '*' || id == '~') {
        accessible = false;
    }
    else accessible = true;
    content = NULL;
}

int Block::is_accessible() {
    return accessible;
}

void Block::change_block_id(char id, Entity* cnt) {
    this->identity = id;
    this->content = cnt;

}
