#ifndef DICE_H
#define DICE_H

#include <nusys.h>

typedef struct
{
    u32 count;
    u32 flags; // shape-pattern-color
    u32 dir;
} Dice;

// Init dice
void init_dice(Dice *dice, u32 settings_flags);

// Shuffle dice
void shuffle_dice(Dice *dice);

u32 dice_to_gfx(Dice *dice, u32 *dice_gfx_ids);

#endif // DICE_H
