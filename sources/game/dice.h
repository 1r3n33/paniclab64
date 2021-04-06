#ifndef DICE_H
#define DICE_H

#include <nusys.h>

typedef struct
{
    // Some game settings (story mode) force shape, patterns, color.
    u32 forced_flags_clear;
    u32 forced_flags_set;
    u32 flags; // shape-pattern-color

    u32 is_dir_enabled;
    u32 dir;
} Dice;

Dice *get_dice();

void init_dice(u32 settings_flags);

void shuffle_dice();

u32 dice_to_gfx(u32 *dice_gfx_ids);

#endif // DICE_H
