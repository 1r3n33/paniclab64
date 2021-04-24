#include "fonts.h"
#include "graphics.h"
#include "init.h"
#include "menu.h"
#include "projection.h"

Mtx menu_triangles_mtx;

Vtx menu_triangles_vtx[6] = {
    {0, 3, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {6, 6, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {6, 0, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},

    {34, 6, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {40, 3, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {34, 0, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
};

f32 menu_triangles_pos[] = {51.0f, 31.0f, 11.0f, -9.0f, -29.0f, -49.0f, -999.9f, -999.9f};

Gfx *render_menu_selection(Gfx *gfx, u32 selection)
{
    gSPTexture(gfx++, 0, 0, 0, 0, G_OFF);
    gDPSetRenderMode(gfx++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 0xf0, 0xf0, 0x50, 0xFF);
    gSPClearGeometryMode(gfx++, 0xFFFFFFFF);

    guTranslate(&menu_triangles_mtx, 20.0f, menu_triangles_pos[selection], 0.0f);
    gSPMatrix(
        gfx++,
        OS_K0_TO_PHYSICAL(&menu_triangles_mtx),
        G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    gSPVertex(gfx++, menu_triangles_vtx, 6, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 3, 4, 5, 0);

    return gfx;
}

void render_menu()
{
    Gfx *gfx = gfxBegin();

    gfx = gfxClearCfb(gfx, GPACK_RGBA5551(0x70, 0xC0, 0x70, 0xFF), G_MAXFBZ);
    gfx = apply_projection(gfx, (f32)SCREEN_WD, (f32)SCREEN_HT);

    gfx = render_string(gfx, "Settings", 0, -20.0f, 80.0f);

    for (u32 i = 0; i <= 13; i++)
    {
        gfx = render_string(gfx, graphics.strings[i].b, (i+1) * 16, graphics.strings[i].x, graphics.strings[i].y);
    }

    gfx = render_menu_selection(gfx, graphics.selection);

    gfxEnd(gfx);
}
