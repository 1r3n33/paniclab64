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

#define GLYPH2(pt, pl, pb, pr, tt, tl, tb, tr)                              \
    {                                                                       \
        {pl, pt, 0, 0, MAKE_U(tl), MAKE_V(tt), 0xff, 0xff, 0xff, 0xff},     \
            {pr, pt, 0, 0, MAKE_U(tr), MAKE_V(tt), 0xff, 0xff, 0xff, 0xff}, \
            {pr, pb, 0, 0, MAKE_U(tr), MAKE_V(tb), 0xff, 0xff, 0xff, 0xff}, \
            {pl, pb, 0, 0, MAKE_U(tl), MAKE_V(tb), 0xff, 0xff, 0xff, 0xff}, \
    }

Mtx glyph_mtxs[256];

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
    ['D'] = GLYPH(5, 10, 1, 19, 11, 24),
    ['E'] = GLYPH(5, 10, 1, 25, 11, 30),
    ['F'] = GLYPH(5, 10, 1, 31, 11, 36),
    ['G'] = GLYPH(5, 10, 1, 37, 11, 42),
    ['H'] = GLYPH(5, 10, 1, 43, 11, 48),
    ['I'] = GLYPH(4, 10, 1, 49, 11, 53),
    ['J'] = GLYPH(5, 10, 1, 54, 11, 59),
    ['K'] = GLYPH(5, 10, 1, 60, 11, 65),
    ['L'] = GLYPH(4, 10, 1, 66, 11, 70),
    ['M'] = GLYPH(7, 10, 1, 71, 11, 78),
    ['N'] = GLYPH(7, 10, 1, 79, 11, 86),
    ['O'] = GLYPH(5, 10, 1, 87, 11, 92),
    ['P'] = GLYPH(5, 10, 1, 93, 11, 98),
    ['Q'] = GLYPH(5, 10, 1, 99, 11, 104),
    ['R'] = GLYPH(5, 10, 1, 105, 11, 110),
    ['S'] = GLYPH(5, 10, 1, 111, 11, 116),
    ['T'] = GLYPH(5, 10, 1, 117, 11, 122),
    ['U'] = GLYPH(5, 10, 12, 1, 22, 6),
    ['V'] = GLYPH(5, 10, 12, 7, 22, 12),
    ['W'] = GLYPH(7, 10, 12, 13, 22, 20),
    ['X'] = GLYPH(6, 10, 12, 21, 22, 27),
    ['Y'] = GLYPH(5, 10, 12, 28, 22, 33),
    ['Z'] = GLYPH(7, 10, 12, 34, 22, 39),
    ['a'] = GLYPH(5, 6, 27, 1, 33, 6),
    ['b'] = GLYPH(4, 10, 23, 7, 33, 11),
    ['c'] = GLYPH(4, 6, 27, 12, 33, 16),
    ['d'] = GLYPH(5, 10, 23, 17, 33, 22),
    ['e'] = GLYPH(4, 6, 27, 23, 33, 27),
    ['f'] = GLYPH(5, 10, 23, 28, 33, 33),
    ['g'] = GLYPH2(6, 0, -2, 5, 27, 34, 35, 39),
    ['h'] = GLYPH(4, 10, 23, 40, 33, 44),
    ['i'] = GLYPH(3, 9, 24, 45, 33, 48),
    ['j'] = GLYPH2(9, 0, -2, 4, 24, 49, 35, 53),
    ['k'] = GLYPH(4, 10, 23, 54, 33, 58),
    ['l'] = GLYPH(3, 10, 23, 59, 33, 62),
    ['m'] = GLYPH(6, 6, 27, 63, 33, 69),
    ['n'] = GLYPH(4, 6, 27, 70, 33, 74),
    ['o'] = GLYPH(4, 6, 27, 75, 33, 79),
    ['p'] = GLYPH2(6, 0, -2, 4, 27, 80, 35, 84),
    ['q'] = GLYPH2(6, 0, -2, 5, 27, 85, 35, 90),
    ['r'] = GLYPH(4, 6, 27, 91, 33, 95),
    ['s'] = GLYPH(4, 6, 27, 96, 33, 100),
    ['t'] = GLYPH(4, 10, 23, 101, 33, 105),
    ['u'] = GLYPH(4, 6, 27, 106, 33, 110),
    ['v'] = GLYPH(4, 6, 27, 111, 33, 115),
    ['w'] = GLYPH(6, 6, 27, 116, 33, 122),
    ['x'] = GLYPH(5, 6, 34, 1, 40, 6),
    ['y'] = GLYPH2(6, 0, -2, 4, 34, 7, 42, 11),
    ['z'] = GLYPH(4, 6, 34, 12, 40, 16),
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
    ['D'] = 5 + 1,
    ['E'] = 5 + 1,
    ['F'] = 5 + 1,
    ['G'] = 5 + 1,
    ['H'] = 5 + 1,
    ['I'] = 4 + 1,
    ['J'] = 5 + 1,
    ['K'] = 5 + 1,
    ['L'] = 4 + 1,
    ['M'] = 7 + 1,
    ['N'] = 7 + 1,
    ['O'] = 5 + 1,
    ['P'] = 5 + 1,
    ['Q'] = 5 + 1,
    ['R'] = 5 + 1,
    ['S'] = 5 + 1,
    ['T'] = 5 + 1,
    ['U'] = 5 + 1,
    ['V'] = 5 + 1,
    ['W'] = 7 + 1,
    ['X'] = 6 + 1,
    ['Y'] = 5 + 1,
    ['Z'] = 7 + 1,
    ['a'] = 5 + 1,
    ['b'] = 4 + 1,
    ['c'] = 4 + 1,
    ['d'] = 5 + 1,
    ['e'] = 4 + 1,
    ['f'] = 5 + 1,
    ['g'] = 5 + 1,
    ['h'] = 4 + 1,
    ['i'] = 3 + 1,
    ['j'] = 4 + 1,
    ['k'] = 4 + 1,
    ['l'] = 3 + 1,
    ['m'] = 6 + 1,
    ['n'] = 4 + 1,
    ['o'] = 4 + 1,
    ['p'] = 4 + 1,
    ['q'] = 5 + 1,
    ['r'] = 4 + 1,
    ['s'] = 4 + 1,
    ['t'] = 4 + 1,
    ['u'] = 4 + 1,
    ['v'] = 4 + 1,
    ['w'] = 6 + 1,
    ['x'] = 5 + 1,
    ['y'] = 4 + 1,
    ['z'] = 4 + 1,
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
    {0x00, 0x00, 0x00, 0x00}, // 0 Not applicable
    {0x00, 0x00, 0x00, 0xFF}, // 1 Black
    {0x1c, 0x91, 0x9b, 0xFF}, // 2 Ref Blue
    {0x62, 0x26, 0x8d, 0xFF}, // 3 Ref Purple
    {0xf3, 0x6a, 0x23, 0xFF}, // 4 Ref Orange
    {0xed, 0x27, 0x44, 0xFF}, // 5 Ref Red
    {0xf0, 0xf0, 0x50, 0xFF}, // 6 Yellow
    {0x70, 0xc0, 0x70, 0xFF}, // 7 Green
    {0xff, 0xff, 0xff, 0xFF}, // 8 White
};

Gfx *render_string(Gfx *gfx, char *str, u32 mtx_id, f32 x, f32 y)
{
    gfx = apply_fonts_texture(gfx);

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);

    // Enable blending
    gDPSetRenderMode(gfx++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

    gSPClearGeometryMode(gfx++, 0xFFFFFFFF);

    gDPSetCombineLERP(
        gfx++,
        0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0,
        0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
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
