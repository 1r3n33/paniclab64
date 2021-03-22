#ifndef CARDS_H
#define CARDS_H

#include <nusys.h>

// Cards
#define MAX_CARDS 32

typedef struct
{
    u32 count;
    u32 flags[MAX_CARDS]; // shape-pattern-color

    u32 blue_dir;
    u32 yellow_dir;
    u32 red_dir;
} Cards;

Cards *get_cards();

// Init cards
u32 init_cards(u32 settings_flags);

// Shuffle cards
void shuffle_cards();

u32 get_cards_start(u32 dice_dir);

u32 get_card_flags(u32 card_id);

// Map to graphics data
u32 cards_to_gfx(u32 *card_gfx_ids);

#endif // CARDS_H
