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
    a = new Block * [k];            // allocate the memory
    srand(time(0));
    for (i = 0; i < k; i++) {
        a[i] = new Block[l];
        for (j = 0; j < l; j++) {
            if (i == k - 1 && j == l - 1 && pot == 0) { // if you are in the last block and no potion has been generated
                a[i][j].init('+');      // generate it here
                continue;
            }
            num = 1 + (rand() % 100);
            if (num >= 1 && num <= 8) sym = '*';    // this block is a tree with a chance of 8%
            else if (num <= 16) sym = '~';          // this block is water with a chance of 8%
            else if (num <= 21 && pot == 0) {       // this block is a potion with a chance of 5%
                pot++;
                sym = '+';
            }
            else sym = ' ';
            a[i][j].init(sym);
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
    
    // spawns werewolves 
    for (int i = 0; i < wer; i++) {
        int temp = true;
        while (temp) {
            int random_x = (rand() % x);    // x depicts height
            int random_y = (rand() % y);    // y depicts width
            if (a[random_x][random_y].is_accessible()) {    // if this random block is empty
                w[i].change_coords(random_x, random_y);     // spawn the entity
                a[random_x][random_y].change_block_id('w', &w[i]);
                a[random_x][random_y].accessible = false;
                temp = false;
            }
        }
    }
    w[wer - 1].strength_boost();            // Make at least one werewolf have 3 strength

    // spawns vampires
    for (int i = 0; i < vam; i++) {
        int temp = true;
        while (temp) {
            int random_x = (rand() % x);    // x depicts height
            int random_y = (rand() % y);    // y depicts width
            if (a[random_x][random_y].is_accessible()) {
                v[i].change_coords(random_x, random_y);
                a[random_x][random_y].change_block_id('v', &v[i]);
                a[random_x][random_y].accessible = false;
                temp = false;
            }
        }
    }
    v[vam - 1].strength_boost();            // Make at least one vampire have 3 strength

    // spawns the Avatar
    int temp = true;
    while (temp) {
        int random_x = (rand() % x);    // x depicts height
        int random_y = (rand() % y);    // y depicts width
        if (a[random_x][random_y].is_accessible()) {
            player.change_coords(random_x, random_y);
            a[random_x][random_y].change_block_id(player.get_team(), &player);
            a[random_x][random_y].accessible = false;
            temp = false;
        }
    } 
}

void Board::print() {
    // print board
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

    // print current time
    string current_time;
    if (this->day_or_night == 1)		//day
        current_time = "day";
    else								//night
        current_time = "night";
    cout << endl <<"Current time: " << current_time << endl;

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

int Board::get_number_of_wer() {
    return this->number_of_werewolves;
}

int Board::get_number_of_vam() {
    return this->number_of_vampires;
}

void Board::reduce_npc(char v_or_w) {
    if (v_or_w == 'v')
        this->number_of_vampires--;
    else if (v_or_w == 'w')
        this->number_of_werewolves--;
}

void Board::make_npc_movement(Vampires* v, Werewolves* w) {
    int num = x * y / 15;
    if (this->day_or_night == 1) {
        for (int i = 0; i < num; i++) {
            if (v[i].is_alive())
                v[i].decide(*this);
        }
        for (int i = 0; i < num ; i++) {
            if (w[i].is_alive())
                w[i].decide(*this);
        }
    }
    else {
        for (int i = 0; i < num; i++) {
            if (w[i].is_alive())
                w[i].decide(*this);
        }
        for (int i = 0; i < num; i++) {
            if (v[i].is_alive())
                v[i].decide(*this);
        }
    }
}

void Board::delete_game(Vampires * v, Werewolves * w) {
    int i;
    delete[] v;
    delete[] w;
    for (i = 0; i < x; i++)
        delete[] a[i];
    delete[] a;
}

void Block::init(char id) {
    identity = id;
    if (id == ' ') {
        accessible = true;
    }
    else accessible = false;
    content = NULL;
}

bool Block::is_accessible() {
    return this->accessible;
}

bool Block::is_accessible_for_avatar() {
    if (this->identity == '+')
        return true;
    else
        return this->accessible;
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
