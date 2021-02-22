#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "matrices.h"
#include "projection.h"
#include "textures.h"

typedef struct
{
    Matrices matrices[MATRICES_LEN];
} Graphics;

extern Graphics graphics;

#endif // GRAPHICS_H
