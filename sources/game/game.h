#ifndef GAME_H
#define GAME_H

#include <nusys.h>
#include "cards.h"
#include "cursors.h"
#include "dice.h"
#include "scores.h"

// Game
typedef struct
{
    u32 card_count;
    Dice dice;
} Game;

// Init the game
void init_game(Game *game);

// Shuffle game
void shuffle_game(Game *game);

// Get position that matches dice configuration
u32 get_solution(Game *game);

extern Game game;

#endif // GAME_H
