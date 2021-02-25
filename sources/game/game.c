#include <nusys.h>
#include <os_time.h>
#include <stdlib.h>
#include "game.h"

#define FLAGS_DIR_BLUE 0x00010000
#define FLAGS_DIR_YELLOW 0x00010001
#define FLAGS_DIR_RED 0x00010002

#define FLAGS_SWAP_SHAPE 0x00020000
#define FLAGS_SWAP_PATTERN 0x00020001
#define FLAGS_SWAP_COLOR 0x00020002

#define FLAGS_VENT 0x00040000

Game game;

void init_game(Game *game)
{
    init_cards(&game->cards);
    init_dice(&game->dice);
    init_cursor(&game->cursor, game->cards.count);
}

void init_cards(Cards *cards)
{
    cards->count = 8 + 3 + 3 + 3; // Number of cards

    // 8 first cards are aliens
    for (u32 i = 0; i < 8; i++)
    {
        cards->flags[i] = i & 7;
        cards->gfx_ids[i] = i & 7;
    }

    // 3 next cards are directions
    cards->flags[8] = FLAGS_DIR_BLUE;
    cards->gfx_ids[8] = 8;
    cards->flags[9] = FLAGS_DIR_YELLOW;
    cards->gfx_ids[9] = 9;
    cards->flags[10] = FLAGS_DIR_RED;
    cards->gfx_ids[10] = 10;

    cards->blue_dir = 8;
    cards->yellow_dir = 9;
    cards->red_dir = 10;

    // 3 next cards are swaps
    cards->flags[11] = FLAGS_SWAP_SHAPE;
    cards->gfx_ids[11] = 11;
    cards->flags[12] = FLAGS_SWAP_PATTERN;
    cards->gfx_ids[12] = 12;
    cards->flags[13] = FLAGS_SWAP_COLOR;
    cards->gfx_ids[13] = 13;

    // 3 next cards are vents
    cards->flags[14] = FLAGS_VENT;
    cards->gfx_ids[14] = 14;
    cards->flags[15] = FLAGS_VENT;
    cards->gfx_ids[15] = 14;
    cards->flags[16] = FLAGS_VENT;
    cards->gfx_ids[16] = 14;
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

    // Keep track of the dir cards (starting points)
    for (u32 i = 0; i < cards->count; i++)
    {
        if (cards->flags[i] == FLAGS_DIR_BLUE)
        {
            cards->blue_dir = i;
        }
        if (cards->flags[i] == FLAGS_DIR_YELLOW)
        {
            cards->yellow_dir = i;
        }
        if (cards->flags[i] == FLAGS_DIR_RED)
        {
            cards->red_dir = i;
        }
    }
}

int check_selection(Game *game)
{
    // Initialize start position and direction
    s32 start = 0;
    s32 dir = 0;
    switch (game->dice.dir)
    {
    case 0: // blue-black clockwise
        start = game->cards.blue_dir;
        dir = -1;
        break;

    case 1: // blue-white anti-clockwise
        start = game->cards.blue_dir;
        dir = 1;
        break;

    case 2: // yellow-black clockwise
        start = game->cards.yellow_dir;
        dir = -1;
        break;

    case 3: // yellow-white anti-clockwise
        start = game->cards.yellow_dir;
        dir = 1;
        break;

    case 4: // red-black clockwise
        start = game->cards.red_dir;
        dir = -1;
        break;

    case 5: // red-white anti-clockwise
        start = game->cards.red_dir;
        dir = 1;
        break;
    }

    // Get initial flags (shape-pattern-color)
    u32 flags = game->dice.flags;

    // Count number of swap to avoid infinite loop
    u32 swap = 0;

    // Know when to check if flags match
    u32 check = 1;

    // Find the correct card pos
    s32 pos = start;
    while (1)
    {
        u32 f = game->cards.flags[pos];

        if (check)
        {
            // Exit if card matches flags
            if (f == flags)
            {
                break;
            }

            // Swap shape flag
            if (f == FLAGS_SWAP_SHAPE)
            {
                flags ^= 0b001;
                swap++;
            }
            // Swap pattern flag
            if (f == FLAGS_SWAP_PATTERN)
            {
                flags ^= 0b010;
                swap++;
            }
            // Swap color flag
            if (f == FLAGS_SWAP_COLOR)
            {
                flags ^= 0b100;
                swap++;
            }

            // If flags go back to original, the game cannot be resolved
            // Stop on the swap card
            if (swap == 6)
            {
                break;
            }
        }

        // Enter/Exit air vents
        if (f == FLAGS_VENT)
        {
            check = !check;
        }

        // Compute next pos
        pos += dir;
        while (pos < 0)
        {
            pos += game->cards.count;
        }
        while (pos >= game->cards.count)
        {
            pos -= game->cards.count;
        }
    }

    // Correct if the cursor pos is correct card pos
    return game->cursor.cur_pos == pos;
}
