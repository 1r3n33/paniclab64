#include <nusys.h>
#include "matrices.h"

void set_card_matrices(Matrices *m, f32 y, f32 rot)
{
    guTranslate(&m->translation, 0.0f, y, 0.0f);
    guRotate(&m->rotation, rot, 0.0f, 0.0f, 1.0f);
    guScale(&m->scale, 1.0f, 1.0f, 1.0f);
}

void set_dice_matrices(Matrices *m, f32 x, f32 y, f32 s)
{
    guTranslate(&m->translation, x, y, 0.0f);
    guRotate(&m->rotation, 0.0f, 0.0f, 0.0f, 1.0f);
    guScale(&m->scale, s, s, s);
}

Gfx *apply_matrices(Gfx *glistp, Matrices *m)
{
    gSPMatrix(
        glistp++,
        OS_K0_TO_PHYSICAL(&m->rotation),
        G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    gSPMatrix(
        glistp++,
        OS_K0_TO_PHYSICAL(&m->translation),
        G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    gSPMatrix(
        glistp++,
        OS_K0_TO_PHYSICAL(&m->scale),
        G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    return glistp;
}
