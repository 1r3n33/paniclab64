#include <nusys.h>
#include <os_time.h>
#include <stdlib.h>
#include "game.h"

Game game;

void fill(Cards *cards)
{
    u32 count = 16; // Number of cards
    cards->count = count;
    for (u32 i=0; i<count; i++)
    {
        cards->gfx_ids[i] = i;
    }
}

void shuffle(Cards *cards)
{
    for (u32 i=cards->count-1; i>0; i--)
    {
        u32 rnd = rand()%(i+1);
        u32 id = cards->gfx_ids[rnd];
        cards->gfx_ids[rnd] = cards->gfx_ids[i];
        cards->gfx_ids[i] = id;
    }
}

void init(Game * game)
{
    u64 time = osGetTime();
    srand((unsigned)time);

    fill(&game->cards);
    shuffle(&game->cards);
}
