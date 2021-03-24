#include <stdlib.h>
#include "cards.h"
#include "flags.h"
#include "settings.h"

Cards cards;

Cards *get_cards()
{
    return &cards;
}

u32 init_cards(u32 settings_flags)
{
    u32 mutations = settings_flags & SETTINGS_FLAG_MUTATIONS;
    u32 air_vents = settings_flags & SETTINGS_FLAG_AIRVENTS;
    u32 directions = mutations | air_vents;

    // 8 cards are amoebas
    u32 i;
    for (i = 0; i < 8; i++)
    {
        cards.flags[i] = i & 7;
    }

    if (directions)
    {
        // 3 cards are directions
        cards.flags[i] = FLAGS_DIR_BLUE;
        cards.blue_dir = i;
        i++;

        cards.flags[i] = FLAGS_DIR_YELLOW;
        cards.yellow_dir = i;
        i++;

        cards.flags[i] = FLAGS_DIR_RED;
        cards.red_dir = i;
        i++;
    }
    else
    {
        cards.blue_dir = 0;
        cards.yellow_dir = 0;
        cards.red_dir = 0;
    }

    if (mutations)
    {
        // 3 cards are mutations
        cards.flags[i++] = FLAGS_SWAP_SHAPE;
        cards.flags[i++] = FLAGS_SWAP_PATTERN;
        cards.flags[i++] = FLAGS_SWAP_COLOR;
    }

    if (air_vents)
    {
        // 3 cards are air vents
        cards.flags[i++] = FLAGS_VENT;
        cards.flags[i++] = FLAGS_VENT;
        cards.flags[i++] = FLAGS_VENT;
    }

    cards.count = i;
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

u32 get_cards_count()
{
    return cards.count;
}

u32 get_cards_start(u32 dice_dir)
{
    switch (dice_dir)
    {
    case 0: // blue-black clockwise
    case 1: // blue-white anti-clockwise
        return cards.blue_dir;

    case 2: // yellow-black clockwise
    case 3: // yellow-white anti-clockwise
        return cards.yellow_dir;

    case 4: // red-black clockwise
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
