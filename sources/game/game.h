#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <nusys.h>
#include "cards.h"
#include "cursors.h"
#include "dice.h"
#include "scores.h"
#include "settings.h"

// Init the game
void init_game(u32 player_count, u32 settings_flags);

// Shuffle game
void shuffle_game();

// Get position that matches dice configuration
u32 get_solution();

#endif // GAME_GAME_H
