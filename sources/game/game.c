#include <nusys.h>
#include <os_time.h>
#include <stdlib.h>
#include "game.h"

Game game;

void init_game(Game *game)
{
    init_cards(&game->cards);
    init_dice(&game->dice);
    init_cursor(&game->cursor);
}

void init_cards(Cards *cards)
{
    u32 count = 16; // Number of cards
    cards->count = count;
    for (u32 i = 0; i < count; i++)
    {
        cards->gfx_ids[i] = i;
    }
}

void init_dice(Dice *dice)
{
    u32 count = 3; // Number of dice
    dice->count = count;

    dice->gfx_ids[DICE_SHAPE] = SHAPE_SQUID;
    dice->gfx_ids[DICE_PATTERN] = PATTERN_STRIPES;
    dice->gfx_ids[DICE_COLOR] = COLOR_BLUE;
}

void shuffle_game(Game *game)
{
    u64 time = osGetTime();
    srand((unsigned)time);

    shuffle_cards(&game->cards);
    shuffle_dice(&game->dice);
}

void shuffle_cards(Cards *cards)
{
    for (u32 i = cards->count - 1; i > 0; i--)
    {
        u32 rnd = rand() % (i + 1);
        u32 id = cards->gfx_ids[rnd];
        cards->gfx_ids[rnd] = cards->gfx_ids[i];
        cards->gfx_ids[i] = id;
    }
}

void shuffle_dice(Dice *dice)
{
    u32 rnd = rand(); // Use random 3 lsb as 0 or 1 enum
    dice->gfx_ids[DICE_SHAPE] = (rnd & 1) >> 0;
    dice->gfx_ids[DICE_PATTERN] = (rnd & 2) >> 1;
    dice->gfx_ids[DICE_COLOR] = (rnd & 4) >> 2;
}
