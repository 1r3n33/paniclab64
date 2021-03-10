#include <nusys.h>
#include <os_time.h>
#include <stdlib.h>
#include "flags.h"
#include "game.h"

Game game;

void init_game(Game *game)
{
    u32 player_count = 2;

    u32 card_count = init_cards();
    game->card_count = card_count;

    init_dice(&game->dice);

    init_cursors(player_count, card_count);

    init_scores();
}

void shuffle_game(Game *game)
{
    u64 time = osGetTime();
    srand((unsigned)time);

    shuffle_cards();
    shuffle_dice(&game->dice);
}

u32 get_solution(Game *game)
{
    // Initialize start position and direction
    s32 start_dir = get_cards_start_dir(game->dice.dir);
    s32 start = start_dir > 0 ? start_dir : -start_dir;
    s32 dir = start_dir > 0 ? 1 : -1;

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
        u32 f = get_card_flags(pos);

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
            pos += game->card_count;
        }
        while (pos >= game->card_count)
        {
            pos -= game->card_count;
        }
    }

    return pos;
}
