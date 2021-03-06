#include <stdlib.h>
#include "cards.h"
#include "flags.h"
#include "settings.h"

Cards cards;

Cards *get_cards()
{
    return &cards;
}

u32 shape_setting_flags[] = {SETTINGS_FLAG_SHAPE_0, SETTINGS_FLAG_SHAPE_1};

u32 init_cards(u32 settings_flags)
{
    u32 mutations = settings_flags & SETTINGS_FLAG_MUTATION_ALL;
    u32 air_vents = settings_flags & SETTINGS_FLAG_AIRVENTS;
    u32 directions = mutations | air_vents;

    // 8 cards are amoebas
    u32 i = 0;
    for (u32 j = 0; j < 8; j++)
    {
        u32 shape = j & 1;
        if (settings_flags & shape_setting_flags[shape])
        {
            cards.flags[i] = j;
            i++;
        }
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
        if (settings_flags & SETTINGS_FLAG_MUTATION_0)
        {
            cards.flags[i++] = FLAGS_SWAP_SHAPE;
        }
        if (settings_flags & SETTINGS_FLAG_MUTATION_1)
        {
            cards.flags[i++] = FLAGS_SWAP_PATTERN;
        }
        if (settings_flags & SETTINGS_FLAG_MUTATION_2)
        {
            cards.flags[i++] = FLAGS_SWAP_COLOR;
        }
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

u32 get_virtual_card_count()
{
    return (cards.count < 12) ? 12 : cards.count;
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
void cards_to_gfx(u32 *card_count, u32 *virtual_card_count, u32 *card_gfx_ids)
{
    *card_count = cards.count;

    // When number of cards is low, it looks nicer to set cards on a bigger virtual circle.
    *virtual_card_count = get_virtual_card_count();

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
}
