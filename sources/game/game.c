#include <nusys.h>
#include <os_time.h>
#include <stdlib.h>
#include "flags.h"
#include "game.h"

void init_game(u32 player_count, u32 settings_flags)
{
    u32 card_count = init_cards(settings_flags);

    init_dice(settings_flags);

    init_cursors(player_count, card_count);

    init_scores();
}

void shuffle_game()
{
    u64 time = osGetTime();
    srand((unsigned)time);

    shuffle_cards();
    shuffle_dice();
}

u32 get_solution()
{
    Dice *dice = get_dice();
    u32 card_count = get_cards_count();

    // Initialize start position and direction
    s32 start = get_cards_start(dice->dir);
    s32 dir = dice->dir & 1 ? 1 : -1;

    // Get initial flags (shape-pattern-color)
    u32 flags = dice->flags;

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
            pos += card_count;
        }
        while (pos >= card_count)
        {
            pos -= card_count;
        }
    }

    return pos;
}
