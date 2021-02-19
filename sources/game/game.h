#ifndef GAME_H
#define GAME_H

#include <nusys.h>
#include "cursor.h"
#include "dice.h"

// Alien properties
#define SHAPE_SQUID 0  // one eyed
#define SHAPE_SLUGGY 1 // two eyed

#define PATTERN_STRIPES 0
#define PATTERN_DOTS 1

#define COLOR_BLUE 0
#define COLOR_ORANGE 1

// Cards
#define MAX_CARDS 16

typedef struct
{
    u32 count;
    u32 flags[MAX_CARDS]; // shape-pattern-color
    u32 gfx_ids[MAX_CARDS];
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
