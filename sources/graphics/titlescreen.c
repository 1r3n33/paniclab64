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

    gfx = render_string(gfx, "\2P\3r\2e\3s\2s \3S\2T\3A\2R\3T", 0, -30.0f, 5.0f);
    gfx = render_string(gfx, "\4P\5r\4e\5s\4s \5S\4T\5A\4R\5T", 16, -30.0f, -10.0f);

    gfxEnd(gfx);
}
