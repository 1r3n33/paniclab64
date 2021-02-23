#ifndef DICE_H
#define DICE_H

#include <nusys.h>

#define DICE_SHAPE 0
#define DICE_PATTERN 1
#define DICE_COLOR 2
#define DICE_DIR 3

#define MAX_DICE 4

typedef struct
{
    u32 count;
    u32 flags; // shape-pattern-color
    u32 dir;
    u32 gfx_ids[MAX_DICE];
} Dice;

// Init dice
void init_dice(Dice *dice);

// Shuffle dice
void shuffle_dice(Dice *dice);

#endif // DICE_H
