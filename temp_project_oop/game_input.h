#pragma once
#include <string>
#include "game.h"


// Checks if the player is stuck by unmovable objects by all 4 directions {up, down, right, left}
bool check_player_really_stuck(Board& games_board, Avatar& player);

// The fuction that starts the game and gets the user input to move the avatar etc
int game_input(Board &games_board, Avatar &player, Vampires* v, Werewolves* w);
