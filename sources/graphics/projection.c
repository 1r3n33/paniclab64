#include "projection.h"

Mtx projection;

Gfx *apply_projection(Gfx *gfx, f32 w, f32 h)
{
    // Compute projection matrix
    // The near clipping plane is a rectangle with the lower-left vertex at (l, b, -n) and the upper-right vertex at (r, t, -n).
    // The far clipping plane is a rectangle with the lower-left vertex at (l, b, -f) and the upper-right vertex at (r, t, -f).
    guOrtho(&projection,
            -w / 2.0F, w / 2.0F,
            -h / 2.0F, h / 2.0F,
            1.0F, -1.0F, 1.0F);

    // Set projection matrix
    gSPMatrix(
        gfx++,
        OS_K0_TO_PHYSICAL(&projection),
        G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

    return gfx;
}
