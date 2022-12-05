#pragma once
#include <string>
#include "game.h"

int game_input(Board games_board, Avatar &player);

void make_avatar_movement(Board b, Avatar &player, std::string direction);