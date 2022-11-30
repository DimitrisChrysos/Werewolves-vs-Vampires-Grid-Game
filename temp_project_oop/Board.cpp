#include <iostream>
#include <cstdlib>
#include <time.h>
#include "game.h"

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

void Board::spawn_entities(Avatar player) {
    int wer, vam;
    wer = vam = x * y / 15;

    int temp = true;
    while (temp) {
        int random_x = 1 + (rand() % x);    // x depicts height
        int random_y = 1 + (rand() % y);    // y depicts width
        if (a[random_x][random_y].is_accessible()) {
            a[random_x][random_y].change_block_id(player.get_team(), &player);
            a[random_x][random_y].accessible = false;
            a[random_x][random_y].x = random_x;
            a[random_x][random_y].x = random_y;
            temp = false;
        }
    }


    
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
    for (i = 0; i < y; i++)
        delete[] a[i];
    delete[] a;
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
