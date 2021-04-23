#include "init.h"
#include "fonts.h"
#include "graphics.h"
#include "projection.h"
#include "story.h"

Mtx story_triangles_mtx;

Vtx story_triangles_vtx[6] = {
    {-70, 3, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-64, 6, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-64, 0, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},

    {64, 6, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {70, 3, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {64, 0, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
};

Gfx *render_story_selection(Gfx *gfx, u32 selection)
{
    gSPTexture(gfx++, 0, 0, 0, 0, G_OFF);
    gDPSetRenderMode(gfx++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    if (selection == 0)
    {
        gDPSetPrimColor(gfx++, 0, 0, 0xf0, 0xf0, 0x50, 0xFF);
    }
    else
    {
        gDPSetPrimColor(gfx++, 0, 0, 0xff, 0xff, 0xff, 0xFF);
    }

    gSPClearGeometryMode(gfx++, 0xFFFFFFFF);

    guTranslate(&story_triangles_mtx, 0.0f, 62.0f, 0.0f);
    gSPMatrix(
        gfx++,
        OS_K0_TO_PHYSICAL(&story_triangles_mtx),
        G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    gSPVertex(gfx++, story_triangles_vtx, 6, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 3, 4, 5, 0);

    return gfx;
}

void render_story()
{
    Gfx *gfx = gfxBegin();

    gfx = gfxClearCfb(gfx, GPACK_RGBA5551(0xE8, 0xA8, 0xB8, 0xFF), G_MAXFBZ);

    gfx = apply_projection(gfx, (f32)SCREEN_WD, (f32)SCREEN_HT);

    gfx = render_string(gfx, graphics.strings[0].b, 0x00, graphics.strings[0].x, graphics.strings[0].y);
    gfx = render_string(gfx, graphics.strings[1].b, 0x20, graphics.strings[1].x, graphics.strings[1].y);

    gfx = render_string(gfx, graphics.strings[2].b, 0x40, graphics.strings[2].x, graphics.strings[2].y);
    gfx = render_string(gfx, graphics.strings[3].b, 0x60, graphics.strings[3].x, graphics.strings[3].y);

    gfx = render_story_selection(gfx, graphics.selection);

    gfxEnd(gfx);
}
