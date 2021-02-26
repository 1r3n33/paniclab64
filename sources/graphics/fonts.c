#include "fonts.h"

#include "../../assets/graphics/fonts_64x64_I_4b.h"

Mtx fonts_mtx;

Gfx *apply_fonts_texture(Gfx *glistp)
{
    // Enable texture, set scaling parameters
    gSPTexture(glistp++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);

    // Switch to combine mode using texture color
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    gDPLoadTextureBlock_4b(glistp++,
                           _pp_table_fonts_64x64_I_4b->pixel.p4, // Pointer to texture image
                           G_IM_FMT_I,                           // Texel format
                           64, 64,                               // Image width and height
                           0,                                    // LUT (palette) index
                           G_TX_WRAP, G_TX_WRAP,                 // Clamp, wrap, mirror frag in s direction
                           6, 6,                                 // s, t masks
                           G_TX_NOLOD, G_TX_NOLOD);              // Shift (not shifted here)

    // Texture palette
    gDPSetTextureLUT(glistp++, G_TT_NONE);

    // Texture perspective correction is turned on during mapping
    gDPSetTexturePersp(glistp++, G_TP_PERSP);
    // Set texture filter
    gDPSetTextureFilter(glistp++, G_TF_BILERP);
    gDPSetTextureConvert(glistp++, G_TC_FILT);

    // This can be ignored until LOD or detail texture is explained
    gDPSetTextureLOD(glistp++, G_TL_TILE);
    gDPSetTextureDetail(glistp++, G_TD_CLAMP);

    return glistp;
}

Gfx *render_glyph(Gfx *glistp, Mtx *m, Vtx *vtx)
{
    gSPMatrix(
        glistp++,
        OS_K0_TO_PHYSICAL(m),
        G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    gSPVertex(glistp++, vtx, 4, 0);
    gSP2Triangles(glistp++, 0, 1, 2, 0, 0, 2, 3, 0);

    return glistp;
}

static Vtx zero[] = {
    {0, 11, 0, 0, 34 << 6, 32 << 6, 0xff, 0xff, 0xff, 0xff},
    {8, 11, 0, 0, 41 << 6, 32 << 6, 0xff, 0xff, 0xff, 0xff},
    {8, 0, 0, 0, 41 << 6, 43 << 6, 0xff, 0xff, 0xff, 0xff},
    {0, 0, 0, 0, 34 << 6, 43 << 6, 0xff, 0xff, 0xff, 0xff},
};

Gfx *render_string(Gfx *glistp, char *str, f32 x, f32 y)
{
    glistp = apply_fonts_texture(glistp);

    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);

    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

    gSPClearGeometryMode(glistp++, 0xFFFFFFFF);
    gSPSetGeometryMode(glistp++, G_SHADE | G_SHADING_SMOOTH);

    guTranslate(&fonts_mtx, x, y, 0.0f);

    while (*str)
    {
        glistp = render_glyph(glistp, &fonts_mtx, zero);
        str++;
    }

    return glistp;
}
