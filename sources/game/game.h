#ifndef GAME_H
#define GAME_H

#include <nusys.h>
#include "cursor.h"
#include "dice.h"

// Cards
#define MAX_CARDS 32

typedef struct
{
    u32 count;
    u32 flags[MAX_CARDS]; // shape-pattern-color
    u32 gfx_ids[MAX_CARDS];

    u32 blue_dir;
    u32 yellow_dir;
    u32 red_dir;
} Cards;

// Game
typedef struct
{
    Cards cards;
    Dice dice;
    Cursor cursor;
} Game;

// Init the game
void init_game(Game *game);

// Init cards
void init_cards(Cards *cards);

// Shuffle game
void shuffle_game(Game *game);

// Shuffle cards
void shuffle_cards(Cards *cards);

// Verify that cursor selection match dice configuration
int check_selection(Game *game);

extern Game game;

#endif // GAME_H
