#include <stdlib.h>
#include "cards.h"
#include "flags.h"

Cards cards;

u32 init_cards()
{
    cards.count = 8 + 3 + 3 + 3; // Number of cards

    // 8 first cards are aliens
    for (u32 i = 0; i < 8; i++)
    {
        cards.flags[i] = i & 7;
    }

    // 3 next cards are directions
    cards.flags[8] = FLAGS_DIR_BLUE;
    cards.flags[9] = FLAGS_DIR_YELLOW;
    cards.flags[10] = FLAGS_DIR_RED;

    cards.blue_dir = 8;
    cards.yellow_dir = 9;
    cards.red_dir = 10;

    // 3 next cards are swaps
    cards.flags[11] = FLAGS_SWAP_SHAPE;
    cards.flags[12] = FLAGS_SWAP_PATTERN;
    cards.flags[13] = FLAGS_SWAP_COLOR;

    // 3 next cards are vents
    cards.flags[14] = FLAGS_VENT;
    cards.flags[15] = FLAGS_VENT;
    cards.flags[16] = FLAGS_VENT;

    return cards.count;
}

void shuffle_cards()
{
    for (u32 i = cards.count - 1; i > 0; i--)
    {
        u32 rnd = rand() % (i + 1);

        u32 flags = cards.flags[rnd];

        cards.flags[rnd] = cards.flags[i];
        cards.flags[i] = flags;
    }

    // Keep track of the dir cards (starting points)
    for (u32 i = 0; i < cards.count; i++)
    {
        if (cards.flags[i] == FLAGS_DIR_BLUE)
        {
            cards.blue_dir = i;
        }
        if (cards.flags[i] == FLAGS_DIR_YELLOW)
        {
            cards.yellow_dir = i;
        }
        if (cards.flags[i] == FLAGS_DIR_RED)
        {
            cards.red_dir = i;
        }
    }
}

s32 get_cards_start_dir(u32 dice_dir)
{
    switch (dice_dir)
    {
    case 0: // blue-black clockwise
        return -cards.blue_dir;

    case 1: // blue-white anti-clockwise
        return cards.blue_dir;

    case 2: // yellow-black clockwise
        return -cards.yellow_dir;

    case 3: // yellow-white anti-clockwise
        return cards.yellow_dir;

    case 4: // red-black clockwise
        return -cards.red_dir;

    case 5: // red-white anti-clockwise
        return cards.red_dir;
    }
}

u32 get_card_flags(u32 card_id)
{
    return cards.flags[card_id];
}

// Map to graphics data
u32 cards_to_gfx(u32 *card_gfx_ids)
{
    for (u32 i = 0; i < cards.count; i++)
    {
        u32 type = cards.flags[i] >> 16;
        switch (type)
        {
        case 0: // Amoebas
            card_gfx_ids[i] = cards.flags[i];
            break;

        case 1: // Directions
            card_gfx_ids[i] = 8 + cards.flags[i] & 0xFF;
            break;

        case 2: // Mutations
            card_gfx_ids[i] = 11 + cards.flags[i] & 0xFF;
            break;

        case 4: // Air vents
            card_gfx_ids[i] = 14;
            break;

        default:
            break;
        }
    }

    return cards.count;
}
