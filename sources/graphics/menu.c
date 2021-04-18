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

f32 menu_triangles_pos[] = {61.0f, 41.0f, 21.0f, 1.0f, -39.0f, -59.0f, -999.9f, -999.9f};

Gfx *render_menu_selection(Gfx *gfx, u32 selection)
{
    gSPTexture(gfx++, 0, 0, 0, 0, G_OFF);
    gDPSetRenderMode(gfx++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 0xf0, 0xf0, 0x50, 0xFF);
    gSPClearGeometryMode(gfx++, 0xFFFFFFFF);

    guTranslate(&menu_triangles_mtx, 18.0f, menu_triangles_pos[selection], 0.0f);
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

    gfx = render_string(gfx, "Settings", 0, -20.0f, 100.0f);

    gfx = render_string(gfx, graphics.text[0], 10, -50.0f, 60.0f);
    gfx = render_string(gfx, graphics.text[1], 20, 30.0f, 60.0f);

    gfx = render_string(gfx, graphics.text[2], 30, -50.0f, 40.0f);
    gfx = render_string(gfx, graphics.text[3], 40, 30.0f, 40.0f);

    gfx = render_string(gfx, graphics.text[4], 50, -50.0f, 20.0f);
    gfx = render_string(gfx, graphics.text[5], 60, 30.0f, 20.0f);

    gfx = render_string(gfx, graphics.text[6], 70, -50.0f, 0.0f);
    gfx = render_string(gfx, graphics.text[7], 80, 30.0f, 0.0f);

    gfx = render_string(gfx, graphics.text[8], 90, -50.0f, -40.0f);
    gfx = render_string(gfx, graphics.text[9], 100, 30.0f, -40.0f);
    gfx = render_string(gfx, graphics.text[10], 110, -50.0f, -60.0f);
    gfx = render_string(gfx, graphics.text[11], 120, 30.0f, -60.0f);

    gfx = render_string(gfx, graphics.text[12], 130, -100.0f, -100.0f);
    gfx = render_string(gfx, graphics.text[13], 140, 80.0f, -100.0f);

    gfx = render_menu_selection(gfx, graphics.selection);

    gfxEnd(gfx);
}
