#include <assert.h>
#include <nusys.h>
#include "../graphic.h"
#include "graphics.h"
#include "render.h"

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
    // Specify the display list buffer
    glistp = gfx_glist;

    // The initialization of RCP
    gfxRCPInit();

    // Clear the frame buffer and the Z-buffer
    gfxClearCfb();

    glistp = apply_projection(glistp, (f32)SCREEN_WD, (f32)SCREEN_HT);

    // Setup texturing
    gSPTexture(glistp++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLUT(glistp++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(glistp++, _pp_table_titlescreen_32x32_CI_8b[0].ppal);
    gDPSetTexturePersp(glistp++, G_TP_PERSP);
    gDPSetTextureFilter(glistp++, G_TF_BILERP);

    // Setup rendering
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glistp++, 0xFFFFFFFF);
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    u32 tile_id = 0;
    for (s32 y = 120; y > -120; y -= 32)
    {
        for (s32 x = -160; x < 160; x += 32)
        {
            glistp = render_quad(glistp, tile_id, (f32)(x + 16), (f32)(y - 16));
            tile_id++;
        }
    }

    // End the construction of the display list
    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);

    // Check if all are put in the array
    assert(glistp - gfx_glist < GFX_GLIST_LEN);

    // Activate the RSP task. Switch display buffers at the end of the task.
    nuGfxTaskStart(gfx_glist,
                   (s32)(glistp - gfx_glist) * sizeof(Gfx),
                   NU_GFX_UCODE_F3DEX, NU_SC_SWAPBUFFER);
}
