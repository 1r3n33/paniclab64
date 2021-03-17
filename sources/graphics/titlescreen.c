#include <nusys.h>
#include "graphics.h"
#include "titlescreen.h"

#include "../../assets/graphics/titlescreen_32x32_CI_8b.h"

// Vertex: xyz, uv, rgba
static Vtx quad_vtx[] = {
    {-16, 16, 0, 0, 0 << 6, 0 << 6, 0x00, 0x00, 0x00, 0xff},
    {16, 16, 0, 0, 31 << 6, 0 << 6, 0x00, 0x00, 0x00, 0xff},
    {16, -16, 0, 0, 31 << 6, 31 << 6, 0x00, 0x00, 0x00, 0xff},
    {-16, -16, 0, 0, 0 << 6, 31 << 6, 0x00, 0x00, 0x00, 0xff},
};

Gfx *render_quad(Gfx *gfx, u32 id, f32 x, f32 y)
{
    set_titlescreen_matrices(&graphics.matrices[id], x, y);

    gfx = apply_matrices(gfx, &graphics.matrices[id]);

    gDPLoadTextureBlock(gfx++,
                        _pp_table_titlescreen_32x32_CI_8b[id].pixel.p8, // Pointer to texture image
                        G_IM_FMT_CI,                                    // Texel format
                        G_IM_SIZ_8b,                                    // Texel size
                        32, 32,                                         // Image width and height
                        0,                                              // LUT (palette) index
                        G_TX_WRAP, G_TX_WRAP,                           // Clamp, wrap, mirror frag in s direction
                        5, 5,                                           // s, t masks
                        G_TX_NOLOD, G_TX_NOLOD);                        // Shift (not shifted here)

    gSPVertex(gfx++, quad_vtx, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 0, 2, 3, 0);

    return gfx;
}

Mtx triangle_mtx;

Vtx triangle_vtx[6] = {
    {0, 6, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {6, 3, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {0, 0, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
};

f32 triangle_pos[] = {9.0f, -11.0f};

u32 triangle_col[2][4] = {
    {0x1c, 0x91, 0x9b, 0xFF},
    {0xf3, 0x6a, 0x23, 0xFF},
};

Gfx *render_titlescreen_selection(Gfx *gfx, u32 selection)
{
    gSPTexture(gfx++, 0, 0, 0, 0, G_OFF);
    gDPSetRenderMode(gfx++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(
        gfx++, 0, 0,
        triangle_col[selection][0], triangle_col[selection][1], triangle_col[selection][2], triangle_col[selection][3]);
    gSPClearGeometryMode(gfx++, 0xFFFFFFFF);

    guTranslate(&triangle_mtx, -42.0f, triangle_pos[selection], 0.0f);
    gSPMatrix(
        gfx++,
        OS_K0_TO_PHYSICAL(&triangle_mtx),
        G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    gSPVertex(gfx++, triangle_vtx, 3, 0);
    gSP1Triangle(gfx++, 0, 1, 2, 0);

    return gfx;
}

void render_titlescreen()
{
    // The initialization of RCP
    Gfx *gfx = gfxBegin();

    // Clear the frame buffer and the Z-buffer
    gfx = gfxClearCfb(gfx, 0, G_MAXFBZ);

    gfx = apply_projection(gfx, (f32)SCREEN_WD, (f32)SCREEN_HT);

    // Setup texturing
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, _pp_table_titlescreen_32x32_CI_8b[0].ppal);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);

    // Setup rendering
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, 0xFFFFFFFF);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    u32 tile_id = 0;
    for (s32 y = 120; y > -120; y -= 32)
    {
        for (s32 x = -160; x < 160; x += 32)
        {
            gfx = render_quad(gfx, tile_id, (f32)(x + 16), (f32)(y - 16));
            tile_id++;
        }
    }

    gfx = render_string(gfx, "\2S\3t\2o\3r\2y \3m\2o\3d\2e", 0, -30.0f, 8.0f);
    gfx = render_string(gfx, "\4B\5a\4t\5t\4l\5e \4m\5o\4d\5e", 16, -30.0f, -12.0f);

    gfx = render_titlescreen_selection(gfx, graphics.selection);

    gfxEnd(gfx);
}
