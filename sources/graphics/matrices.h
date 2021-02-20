#ifndef MATRICES_H
#define MATRICES_H

#include <nusys.h>

#define MATRICES_LEN 32

typedef struct
{
    Mtx translation;
    Mtx rotation;
    Mtx scale;
} Matrices;

void set_card_matrices(Matrices *m, f32 y, f32 rot);

void set_dice_matrices(Matrices *m, f32 x, f32 y, f32 s);

Gfx *apply_matrices(Gfx *glistp, Matrices *m);

#endif // MATRICES_H
