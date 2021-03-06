#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "fonts.h"
#include "init.h"
#include "matrices.h"
#include "projection.h"
#include "textures.h"

typedef struct
{
    Matrices matrices[MATRICES_LEN];
    u32 cursors[4];
    char text[32][32];
} Graphics;

extern Graphics graphics;

#endif // GRAPHICS_H
