#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "fonts.h"
#include "init.h"
#include "matrices.h"
#include "projection.h"
#include "textures.h"
#include "../utils/stringbuilder.h"

typedef struct
{
    u32 selection;

    Matrices matrices[MATRICES_LEN];

    u32 card_count;
    u32 virtual_card_count;
    u32 card_gfx_ids[32];

    u32 dice_count;
    u32 dice_gfx_ids[4];

    u32 cursor_count;
    u32 cursors[4];

    String strings[32];

} Graphics;

extern Graphics graphics;

#endif // GRAPHICS_H
