#include <stdlib.h>
#include "dice.h"
#include "settings.h"

Dice dice;

Dice *get_dice()
{
    return &dice;
}

void init_dice(u32 settings_flags)
{
    dice.forced_flags_clear = ~0;
    dice.forced_flags_set = 0;

    u32 is_shape_forced = ((settings_flags & (SETTINGS_FLAG_SHAPE_0 | SETTINGS_FLAG_SHAPE_1)) != (SETTINGS_FLAG_SHAPE_0 | SETTINGS_FLAG_SHAPE_1));
    if (is_shape_forced)
    {
        dice.forced_flags_clear = ~0x1;
        dice.forced_flags_set = (settings_flags & SETTINGS_FLAG_SHAPE_0) ? 0 : 1;
    }

    // If air vents or mutations is not set we only need the 3 first dice
    dice.is_dir_enabled = (settings_flags & (SETTINGS_FLAG_AIRVENTS | SETTINGS_FLAG_MUTATIONS)) ? 1 : 0;

    dice.flags = 0;
    dice.dir = 0;
}

void shuffle_dice()
{
    u32 rnd = rand();
    dice.flags = rnd & 7;
    dice.dir = ((rnd & 0b00111000) >> 3) % 6;

    dice.flags &= dice.forced_flags_clear;
    dice.flags |= dice.forced_flags_set;
}

u32 dice_to_gfx(u32 *dice_gfx_ids)
{
    u32 count = 0;

    if (dice.forced_flags_clear & 0x1)
    {
        dice_gfx_ids[count++] = 15 + ((dice.flags & 0x1) >> 0); // shape
    }

    if (dice.forced_flags_clear & 0x2)
    {
        dice_gfx_ids[count++] = 17 + ((dice.flags & 0x2) >> 1); // pattern
    }

    if (dice.forced_flags_clear & 0x4)
    {
        dice_gfx_ids[count++] = 19 + ((dice.flags & 0x4) >> 2); // color
    }

    if (dice.is_dir_enabled)
    {
        dice_gfx_ids[count++] = 21 + dice.dir;
    }

    return count;
}
