#include "fonts.h"

#include "../../assets/graphics/fonts_128x64_I_4b.h"

#define MAKE_U(u) (((u - 1) << 6) | (1 << 5))
#define MAKE_V(v) (((v - 1) << 6) | (1 << 5))

#define GLYPH(w, h, t, l, b, r)                                         \
    {                                                                   \
        {0, h, 0, 0, MAKE_U(l), MAKE_V(t), 0xff, 0xff, 0xff, 0xff},     \
            {w, h, 0, 0, MAKE_U(r), MAKE_V(t), 0xff, 0xff, 0xff, 0xff}, \
            {w, 0, 0, 0, MAKE_U(r), MAKE_V(b), 0xff, 0xff, 0xff, 0xff}, \
            {0, 0, 0, 0, MAKE_U(l), MAKE_V(b), 0xff, 0xff, 0xff, 0xff}, \
    }

Mtx glyph_mtxs[32];

static Vtx glyphes[128][4] = {
    ['A'] = GLYPH(5, 10, 1, 1, 11, 6),
    ['B'] = GLYPH(5, 10, 1, 7, 11, 12),
    ['C'] = GLYPH(5, 10, 1, 13, 11, 18),
    ['U'] = GLYPH(5, 10, 12, 1, 22, 6),
    ['V'] = GLYPH(5, 10, 12, 7, 22, 12),
    ['W'] = GLYPH(7, 10, 12, 13, 22, 20),
};

static u32 spaces[128] = {
    ['A'] = 5 + 1,
    ['B'] = 5 + 1,
    ['C'] = 5 + 1,
    ['U'] = 5 + 1,
    ['V'] = 5 + 1,
    ['W'] = 7 + 1,
};

Gfx *apply_fonts_texture(Gfx *glistp)
{
    // Enable texture, set scaling parameters
    gSPTexture(glistp++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);

    // Switch to combine mode using texture color
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    gDPLoadTextureBlock_4b(glistp++,
                           _pp_table_fonts_128x64_I_4b->pixel.p4, // Pointer to texture image
                           G_IM_FMT_I,                            // Texel format
                           128, 64,                               // Image width and height
                           0,                                     // LUT (palette) index
                           G_TX_WRAP, G_TX_WRAP,                  // Clamp, wrap, mirror frag in s direction
                           7, 6,                                  // s, t masks
                           G_TX_NOLOD, G_TX_NOLOD);               // Shift (not shifted here)

    // Texture palette
    gDPSetTextureLUT(glistp++, G_TT_NONE);

    // Texture perspective correction is turned on during mapping
    gDPSetTexturePersp(glistp++, G_TP_PERSP);
    // Set texture filter
    gDPSetTextureFilter(glistp++, G_TF_POINT);
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

Gfx *render_string(Gfx *glistp, char *str, f32 x, f32 y)
{
    glistp = apply_fonts_texture(glistp);

    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);

    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

    gSPClearGeometryMode(glistp++, 0xFFFFFFFF);
    gSPSetGeometryMode(glistp++, G_SHADE | G_SHADING_SMOOTH);

    u32 i = 0;
    while (str[i])
    {
        guTranslate(&glyph_mtxs[i], x, y, 0.0f);
        glistp = render_glyph(glistp, &glyph_mtxs[i], glyphes[str[i]]);
        x += spaces[str[i]];
        i++;
    }

    return glistp;
}
