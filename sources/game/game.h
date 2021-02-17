#ifndef GAME_H
#define GAME_H

#include <nusys.h>
#include "cursor.h"

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
    u32 gfx_ids[MAX_CARDS];
} Cards;

// Dice
#define DICE_SHAPE 0
#define DICE_PATTERN 1
#define DICE_COLOR 2

#define MAX_DICE 4

typedef struct
{
    u32 count;
    u32 gfx_ids[MAX_DICE];
} Dice;

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

// Init dice
void init_dice(Dice *dice);

// Shuffle game
void shuffle_game(Game *game);

// Shuffle cards
void shuffle_cards(Cards *cards);

// Shuffle dice
void shuffle_dice(Dice *dice);

extern Game game;

#endif // GAME_H
