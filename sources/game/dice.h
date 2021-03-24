#ifndef DICE_H
#define DICE_H

#include <nusys.h>

typedef struct
{
    u32 count;
    u32 flags; // shape-pattern-color
    u32 dir;
} Dice;

Dice *get_dice();

void init_dice(u32 settings_flags);

void shuffle_dice();

u32 dice_to_gfx(u32 *dice_gfx_ids);

#endif // DICE_H
