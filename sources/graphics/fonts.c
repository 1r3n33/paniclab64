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
    [' '] = GLYPH(0, 0, 0, 0, 0, 0),
    ['0'] = GLYPH(6, 10, 53, 1, 63, 7),
    ['1'] = GLYPH(6, 10, 53, 7, 63, 13),
    ['2'] = GLYPH(6, 10, 53, 13, 63, 19),
    ['3'] = GLYPH(6, 10, 53, 20, 63, 26),
    ['4'] = GLYPH(6, 10, 53, 27, 63, 33),
    ['5'] = GLYPH(6, 10, 53, 34, 63, 40),
    ['6'] = GLYPH(6, 10, 53, 41, 63, 47),
    ['7'] = GLYPH(6, 10, 53, 48, 63, 54),
    ['8'] = GLYPH(6, 10, 53, 55, 63, 61),
    ['9'] = GLYPH(6, 10, 53, 62, 63, 68),
    ['A'] = GLYPH(5, 10, 1, 1, 11, 6),
    ['B'] = GLYPH(5, 10, 1, 7, 11, 12),
    ['C'] = GLYPH(5, 10, 1, 13, 11, 18),
    ['P'] = GLYPH(5, 10, 1, 93, 11, 98),
    ['R'] = GLYPH(5, 10, 1, 105, 11, 110),
    ['S'] = GLYPH(5, 10, 1, 111, 11, 116),
    ['T'] = GLYPH(5, 10, 1, 117, 11, 122),
    ['U'] = GLYPH(5, 10, 12, 1, 22, 6),
    ['V'] = GLYPH(5, 10, 12, 7, 22, 12),
    ['W'] = GLYPH(7, 10, 12, 13, 22, 20),
    ['e'] = GLYPH(4, 6, 27, 23, 33, 27),
    ['r'] = GLYPH(4, 6, 27, 91, 33, 95),
    ['s'] = GLYPH(4, 6, 27, 96, 33, 100),
};

static u32 spaces[128] = {
    [' '] = 4 + 1,
    ['0'] = 6 + 1,
    ['1'] = 6 + 1,
    ['2'] = 6 + 1,
    ['3'] = 6 + 1,
    ['4'] = 6 + 1,
    ['5'] = 6 + 1,
    ['6'] = 6 + 1,
    ['7'] = 6 + 1,
    ['8'] = 6 + 1,
    ['9'] = 6 + 1,
    ['A'] = 5 + 1,
    ['B'] = 5 + 1,
    ['C'] = 5 + 1,
    ['P'] = 5 + 1,
    ['R'] = 5 + 1,
    ['S'] = 5 + 1,
    ['T'] = 5 + 1,
    ['U'] = 5 + 1,
    ['V'] = 5 + 1,
    ['W'] = 7 + 1,
    ['e'] = 4 + 1,
    ['r'] = 4 + 1,
    ['s'] = 4 + 1,
};

Gfx *apply_fonts_texture(Gfx *gfx)
{
    // Enable texture, set scaling parameters
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);

    gDPLoadTextureBlock_4b(gfx++,
                           _pp_table_fonts_128x64_I_4b->pixel.p4, // Pointer to texture image
                           G_IM_FMT_I,                            // Texel format
                           128, 64,                               // Image width and height
                           0,                                     // LUT (palette) index
                           G_TX_WRAP, G_TX_WRAP,                  // Clamp, wrap, mirror frag in s direction
                           7, 6,                                  // s, t masks
                           G_TX_NOLOD, G_TX_NOLOD);               // Shift (not shifted here)

    // Texture palette
    gDPSetTextureLUT(gfx++, G_TT_NONE);

    // Texture perspective correction is turned on during mapping
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    // Set texture filter
    gDPSetTextureFilter(gfx++, G_TF_POINT);
    gDPSetTextureConvert(gfx++, G_TC_FILT);

    // This can be ignored until LOD or detail texture is explained
    gDPSetTextureLOD(gfx++, G_TL_TILE);
    gDPSetTextureDetail(gfx++, G_TD_CLAMP);

    return gfx;
}

Gfx *render_glyph(Gfx *gfx, Mtx *m, Vtx *vtx)
{
    gSPMatrix(
        gfx++,
        OS_K0_TO_PHYSICAL(m),
        G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    gSPVertex(gfx++, vtx, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 0, 2, 3, 0);

    return gfx;
}

u32 font_colors[32][4] = {
    {0x00, 0x00, 0x00, 0x00}, // Not applicable
    {0x00, 0x00, 0x00, 0xFF}, // Black
    {0x1c, 0x91, 0x9b, 0xFF}, // Ref Blue
    {0x62, 0x26, 0x8d, 0xFF}, // Ref Purple
    {0xf3, 0x6a, 0x23, 0xFF}, // Ref Orange
    {0xed, 0x27, 0x44, 0xFF}, // Ref Red
};

Gfx *render_string(Gfx *gfx, char *str, u32 mtx_id, f32 x, f32 y)
{
    gfx = apply_fonts_texture(gfx);

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);

    // Enable blending
    gDPSetRenderMode(gfx++, G_RM_AA_XLU_SURF2, G_RM_AA_XLU_SURF2);

    gSPClearGeometryMode(gfx++, 0xFFFFFFFF);

    gDPSetCombineMode(gfx++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);

    u32 i = 0;
    u32 j = 0;
    while (str[i])
    {
        if (str[i] < 32)
        {
            u32 *color = font_colors[str[i]];
            gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        }
        else
        {
            guTranslate(&glyph_mtxs[mtx_id + j], x, y, 0.0f);
            gfx = render_glyph(gfx, &glyph_mtxs[mtx_id + j], glyphes[str[i]]);
            x += spaces[str[i]];
            j++;
        }
        i++;
    }
    return gfx;
}
