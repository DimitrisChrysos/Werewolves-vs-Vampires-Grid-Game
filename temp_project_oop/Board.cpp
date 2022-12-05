#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <vector>
#include "game.h"

using namespace std;

Board::Board(int k, int l, int number_of_wer, int number_of_vam) : x(k), y(l) {
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

    int random = 1 + (rand() % 2);  // to randomly declare if we start at night -> [2] or day -> [1]
    this->day_or_night = random;

    this->number_of_werewolves = number_of_wer;
    this->number_of_vampires = number_of_vam;
}

Board::~Board() {}

int Board::getx() {
    return x;
}

int Board::gety() {
    return y;
}

void Board::spawn_entities(Avatar &player, Vampires * v, Werewolves * w) {
    srand(time(0));
    int wer, vam;
    wer = vam = x * y / 15;
    for (int i = 0; i < wer; i++) {
        int temp = true;
        while (temp) {
            int random_x = (rand() % x);    // x depicts height
            int random_y = (rand() % y);    // y depicts width
            if (a[random_x][random_y].is_accessible()) {
                w[i].change_coords(random_x, random_y);
                a[random_x][random_y].change_block_id('w', &w[i]);
                a[random_x][random_y].accessible = false;
                a[random_x][random_y].x = random_x;
                a[random_x][random_y].y = random_y;
                temp = false;
            }
        }
    }

    for (int i = 0; i < vam; i++) {
        int temp = true;
        while (temp) {
            int random_x = (rand() % x);    // x depicts height
            int random_y = (rand() % y);    // y depicts width
            if (a[random_x][random_y].is_accessible()) {
                v[i].change_coords(random_x, random_y);
                a[random_x][random_y].change_block_id('v', &v[i]);
                a[random_x][random_y].accessible = false;
                a[random_x][random_y].x = random_x;
                a[random_x][random_y].y = random_y;
                temp = false;
            }
        }
    }

    int temp = true;
    while (temp) {
        int random_x = (rand() % x);    // x depicts height
        int random_y = (rand() % y);    // y depicts width
        if (a[random_x][random_y].is_accessible()) {
            player.change_coords(random_x, random_y);
            a[random_x][random_y].change_block_id(player.get_team(), &player);
            a[random_x][random_y].accessible = false;
            a[random_x][random_y].x = random_x;
            a[random_x][random_y].y = random_y;
            temp = false;
        }
    } 
}

void Board::print() {
    int i, j;
    cout << endl;
    for (j = 0; j < 2 * y + 1; j++) {
        cout << "-";
    }
    cout << endl;
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            cout << "|" << a[i][j].identity;
            if (j == y - 1) {
                cout << "|";
            }
        }
        cout << endl;
        for (j = 0; j < 2*y + 1; j++) {
            cout << "-";
        }
        cout << endl;
    }
}

void Board::change_time() {
    if (this->day_or_night == 1)
        day_or_night = 2;
    else
        day_or_night = 1;
}

int Board::return_time() {
    return this->day_or_night;
}

void Board::make_npc_movement(Vampires* v, Werewolves* w) {
    if (this->day_or_night == 1) {
        for (int i = 0; i < this->number_of_vampires; i++) {
            if (v[i].is_alive())
                v[i].decide(*this);
        }
        for (int i = 0; i < this->number_of_werewolves ; i++) {
            if (w[i].is_alive())
                w[i].decide(*this);
        }
    }
    else {
        for (int i = 0; i < this->number_of_vampires; i++) {
            if (w[i].is_alive())
                w[i].decide(*this);
        }
        for (int i = 0; i < this->number_of_werewolves; i++) {
            if (v[i].is_alive())
                v[i].decide(*this);
        }
    }
}

void Board::delete_game(Vampires * v, Werewolves * w) {
    int i;
    delete[] v;
    delete[] w;
    for (i = 0; i < y; i++)
        delete[] a[i];
    delete[] a;
}

void Block::init(int a, int b, char id) {
    x = a; y = b; identity = id;
    if (id == ' ') {
        accessible = true;
    }
    else accessible = false;
    content = NULL;
}

int Block::is_accessible() {
    return accessible;
}

void Block::change_block_id(char id, Entity* cnt) {
    this->identity = id;
    this->content = cnt;
    if (id == ' ') accessible = true;
    else accessible = false;
}

Entity* Block::get_ent() {
    return content;
}

char Block::get_id() {
    return identity;
}