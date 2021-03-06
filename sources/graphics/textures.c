#include "textures.h"

#include "../../assets/graphics/sq_bl_st_32x32_CI_4b.h"
#include "../../assets/graphics/sq_or_st_32x32_CI_4b.h"
#include "../../assets/graphics/sq_bl_dt_32x32_CI_4b.h"
#include "../../assets/graphics/sq_or_dt_32x32_CI_4b.h"
#include "../../assets/graphics/sl_bl_st_32x32_CI_4b.h"
#include "../../assets/graphics/sl_or_st_32x32_CI_4b.h"
#include "../../assets/graphics/sl_bl_dt_32x32_CI_4b.h"
#include "../../assets/graphics/sl_or_dt_32x32_CI_4b.h"
#include "../../assets/graphics/dice_sq_32x32_CI_4b.h"
#include "../../assets/graphics/dice_sl_32x32_CI_4b.h"
#include "../../assets/graphics/dice_st_32x32_CI_4b.h"
#include "../../assets/graphics/dice_dt_32x32_CI_4b.h"
#include "../../assets/graphics/dice_bl_32x32_CI_4b.h"
#include "../../assets/graphics/dice_or_32x32_CI_4b.h"
#include "../../assets/graphics/dice_rb_32x32_CI_4b.h"
#include "../../assets/graphics/dice_rw_32x32_CI_4b.h"
#include "../../assets/graphics/dice_yb_32x32_CI_4b.h"
#include "../../assets/graphics/dice_yw_32x32_CI_4b.h"
#include "../../assets/graphics/dice_bb_32x32_CI_4b.h"
#include "../../assets/graphics/dice_bw_32x32_CI_4b.h"
#include "../../assets/graphics/dir_b_32x32_CI_4b.h"
#include "../../assets/graphics/dir_y_32x32_CI_4b.h"
#include "../../assets/graphics/dir_r_32x32_CI_4b.h"
#include "../../assets/graphics/swap_shape_32x32_CI_4b.h"
#include "../../assets/graphics/swap_pattern_32x32_CI_4b.h"
#include "../../assets/graphics/swap_color_32x32_CI_4b.h"
#include "../../assets/graphics/vent_32x32_CI_4b.h"

static PalPixel *textures[32] = {
    _pp_table_sq_bl_st_32x32_CI_4b,
    _pp_table_sl_bl_st_32x32_CI_4b,
    _pp_table_sq_bl_dt_32x32_CI_4b,
    _pp_table_sl_bl_dt_32x32_CI_4b,
    _pp_table_sq_or_st_32x32_CI_4b,
    _pp_table_sl_or_st_32x32_CI_4b,
    _pp_table_sq_or_dt_32x32_CI_4b,
    _pp_table_sl_or_dt_32x32_CI_4b,
    _pp_table_dir_b_32x32_CI_4b,
    _pp_table_dir_y_32x32_CI_4b,
    _pp_table_dir_r_32x32_CI_4b,
    _pp_table_swap_shape_32x32_CI_4b,
    _pp_table_swap_pattern_32x32_CI_4b,
    _pp_table_swap_color_32x32_CI_4b,
    _pp_table_vent_32x32_CI_4b,
    _pp_table_dice_sq_32x32_CI_4b,
    _pp_table_dice_sl_32x32_CI_4b,
    _pp_table_dice_st_32x32_CI_4b,
    _pp_table_dice_dt_32x32_CI_4b,
    _pp_table_dice_bl_32x32_CI_4b,
    _pp_table_dice_or_32x32_CI_4b,
    _pp_table_dice_bb_32x32_CI_4b,
    _pp_table_dice_bw_32x32_CI_4b,
    _pp_table_dice_yb_32x32_CI_4b,
    _pp_table_dice_yw_32x32_CI_4b,
    _pp_table_dice_rb_32x32_CI_4b,
    _pp_table_dice_rw_32x32_CI_4b};

Gfx *apply_texture(Gfx *gfx, u32 tex_id)
{
    // Enable texture, set scaling parameters
    gSPTexture(gfx++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);

    // Switch to combine mode using texture color
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    gDPLoadTextureBlock_4b(gfx++,
                           textures[tex_id]->pixel.p4, // Pointer to texture image
                           G_IM_FMT_CI,                // Texel format
                           32, 32,                     // Image width and height
                           0,                          // LUT (palette) index
                           G_TX_WRAP, G_TX_WRAP,       // Clamp, wrap, mirror frag in s direction
                           5, 5,                       // s, t masks
                           G_TX_NOLOD, G_TX_NOLOD);    // Shift (not shifted here)

    // Texture palette
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx++, 0, textures[tex_id]->ppal);

    // Texture perspective correction is turned on during mapping
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    // Set texture filter
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    // This can be ignored until LOD or detail texture is explained
    gDPSetTextureLOD(gfx++, G_TL_TILE);
    gDPSetTextureDetail(gfx++, G_TD_CLAMP);

    return gfx;
}
