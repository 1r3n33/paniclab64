#include <stdlib.h>
#include "dice.h"
#include "game.h"

void init_dice(Dice *dice)
{
    u32 count = 4; // Number of dice
    dice->count = count;

    dice->gfx_ids[DICE_SHAPE] = 0;
    dice->gfx_ids[DICE_PATTERN] = 0;
    dice->gfx_ids[DICE_COLOR] = 0;
    dice->gfx_ids[DICE_DIR] = 0;
}

void shuffle_dice(Dice *dice)
{
    u32 rnd = rand();
    dice->flags = rnd & 7;
    dice->gfx_ids[DICE_SHAPE] = (rnd & 0b00000001) >> 0;
    dice->gfx_ids[DICE_PATTERN] = (rnd & 0b00000010) >> 1;
    dice->gfx_ids[DICE_COLOR] = (rnd & 0b00000100) >> 2;
    dice->gfx_ids[DICE_DIR] = ((rnd & 0b00111000) >> 3) % 6;
}
