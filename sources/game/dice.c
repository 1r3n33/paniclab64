#include <stdlib.h>
#include "dice.h"
#include "game.h"

void init_dice(Dice *dice)
{
    u32 count = 3; // Number of dice
    dice->count = count;

    dice->gfx_ids[DICE_SHAPE] = SHAPE_SQUID;
    dice->gfx_ids[DICE_PATTERN] = PATTERN_STRIPES;
    dice->gfx_ids[DICE_COLOR] = COLOR_BLUE;
}

void shuffle_dice(Dice *dice)
{
    u32 rnd = rand(); // Use random 3 lsb as 0 or 1 enum
    dice->flags = rnd & 7;
    dice->gfx_ids[DICE_SHAPE] = (rnd & 1) >> 0;
    dice->gfx_ids[DICE_PATTERN] = (rnd & 2) >> 1;
    dice->gfx_ids[DICE_COLOR] = (rnd & 4) >> 2;
}
