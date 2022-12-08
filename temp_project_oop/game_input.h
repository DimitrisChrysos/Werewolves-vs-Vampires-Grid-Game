#pragma once
#include <string>
#include "game.h"

bool check_player_really_stuck(Board& games_board, Avatar& player);

int game_input(Board &games_board, Avatar &player, Vampires* v, Werewolves* w);
