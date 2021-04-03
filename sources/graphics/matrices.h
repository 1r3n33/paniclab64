#ifndef MATRICES_H
#define MATRICES_H

#include <nusys.h>

#define MATRICES_LEN 80

typedef struct
{
    Mtx translation;
    Mtx rotation;
    Mtx scale;
} Matrices;

void set_titlescreen_matrices(Matrices *m, f32 x, f32 y);

void set_card_matrices(Matrices *m, f32 y, f32 r, f32 s);

void set_dice_matrices(Matrices *m, f32 x, f32 y, f32 s);

Gfx *apply_matrices(Gfx *gfx, Matrices *m);

#endif // MATRICES_H
