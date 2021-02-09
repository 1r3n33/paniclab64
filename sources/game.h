#ifndef CARDS_H
#define CARDS_H

#include <nusys.h>
#define MAX_CARDS 16

typedef struct
{
    u32 count;
    u32 gfx_ids[MAX_CARDS];
} Cards;

typedef struct
{
    Cards cards;
}  Game;


// Fill and shuffle cards
void fill(Cards * cards);

// Init the game
void init(Game *game);

extern Game game;

#endif // CARDS_H
