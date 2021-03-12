#include <stdlib.h>
#include "dice.h"
#include "game.h"

void init_dice(Dice *dice, u32 settings_flags)
{
    // If settings_flags is not set we only need the 3 first dice
    dice->count = settings_flags ? 4 : 3;

    dice->flags = 0;
    dice->dir = 0;
}

void shuffle_dice(Dice *dice)
{
    u32 rnd = rand();
    dice->flags = rnd & 7;
    dice->dir = ((rnd & 0b00111000) >> 3) % 6;
}

u32 dice_to_gfx(Dice *dice, u32 *dice_gfx_ids)
{
    dice_gfx_ids[0] = 15 + ((dice->flags & 0b00000001) >> 0); // shape
    dice_gfx_ids[1] = 17 + ((dice->flags & 0b00000010) >> 1); // pattern
    dice_gfx_ids[2] = 19 + ((dice->flags & 0b00000100) >> 2); // color
    dice_gfx_ids[3] = 21 + dice->dir;
    return dice->count;
}
