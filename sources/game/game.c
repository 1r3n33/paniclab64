#include <nusys.h>
#include <os_time.h>
#include <stdlib.h>
#include "game.h"

Game game;

void init_game(Game *game)
{
    init_cards(&game->cards);
    init_dice(&game->dice);
    init_cursor(&game->cursor, game->cards.count);
}

void init_cards(Cards *cards)
{
    cards->count = 8 + 3; // Number of cards

    // 8 first cards are aliens
    for (u32 i = 0; i < 8; i++)
    {
        cards->flags[i] = i & 7;
        cards->gfx_ids[i] = i & 7;
    }

    // 3 next cards are directions
    cards->flags[8] = 0xFFffFFff;
    cards->gfx_ids[8] = 8;
    cards->flags[9] = 0xFFffFFff;
    cards->gfx_ids[9] = 9;
    cards->flags[10] = 0xFFffFFff;
    cards->gfx_ids[10] = 10;
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

        u32 flags = cards->flags[rnd];
        u32 gfx_id = cards->gfx_ids[rnd];

        cards->flags[rnd] = cards->flags[i];
        cards->flags[i] = flags;

        cards->gfx_ids[rnd] = cards->gfx_ids[i];
        cards->gfx_ids[i] = gfx_id;
    }
}

int check_selection(Game *game)
{
    u32 cur = game->cursor.cur_pos;
    u32 card = game->cards.flags[cur];
    u32 dice = game->dice.flags;
    return card == dice;
}
