#include <assert.h>
#include <nusys.h>
#include "game/game.h"
#include "graphic.h"
#include "graphics/graphics.h"

#include "../assets/graphics/sq_bl_st_32x32_CI_4b.h"
#include "../assets/graphics/sq_or_st_32x32_CI_4b.h"
#include "../assets/graphics/sq_bl_dt_32x32_CI_4b.h"
#include "../assets/graphics/sq_or_dt_32x32_CI_4b.h"
#include "../assets/graphics/sl_bl_st_32x32_CI_4b.h"
#include "../assets/graphics/sl_or_st_32x32_CI_4b.h"
#include "../assets/graphics/sl_bl_dt_32x32_CI_4b.h"
#include "../assets/graphics/sl_or_dt_32x32_CI_4b.h"
#include "../assets/graphics/dice_sq_32x32_CI_4b.h"
#include "../assets/graphics/dice_sl_32x32_CI_4b.h"
#include "../assets/graphics/dice_st_32x32_CI_4b.h"
#include "../assets/graphics/dice_dt_32x32_CI_4b.h"
#include "../assets/graphics/dice_bl_32x32_CI_4b.h"
#include "../assets/graphics/dice_or_32x32_CI_4b.h"
#include "../assets/graphics/dice_rb_32x32_CI_4b.h"
#include "../assets/graphics/dice_rw_32x32_CI_4b.h"
#include "../assets/graphics/dice_yb_32x32_CI_4b.h"
#include "../assets/graphics/dice_yw_32x32_CI_4b.h"
#include "../assets/graphics/dice_bb_32x32_CI_4b.h"
#include "../assets/graphics/dice_bw_32x32_CI_4b.h"

void shadetri(Matrices *matrices, int type);

u32 renderCards(Cards *cards, u32 id);

u32 renderDice(Dice *dice, u32 id);

void renderCursor(Matrices *m);

/* Make the display list and activate the task. */

void makeDL00(Game *game)
{
  /* Specify the display list buffer  */
  glistp = gfx_glist;

  /*  The initialization of RCP  */
  gfxRCPInit();

  /* Clear the frame buffer and the Z-buffer  */
  gfxClearCfb();

  // Compute projection matrix
  guOrtho(&gfx_dynamic.projection,
          -(float)SCREEN_WD / 2.0F, (float)SCREEN_WD / 2.0F,
          -(float)SCREEN_HT / 2.0F, (float)SCREEN_HT / 2.0F,
          1.0F, 10.0F, 1.0F);

  // Set projection matrix
  gSPMatrix(
      glistp++,
      OS_K0_TO_PHYSICAL(&gfx_dynamic.projection),
      G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

  u32 mtx_id = 0;
  mtx_id = renderCards(&game->cards, mtx_id);
  mtx_id = renderDice(&game->dice, mtx_id);

  // Draw cursor
  renderCursor(&graphics.matrices[game->cursor.cur_pos]);

  /* End the construction of the display list  */
  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  /* Check if all are put in the array  */
  assert(glistp - gfx_glist < GFX_GLIST_LEN);

  /* Activate the RSP task. Switch display buffers at the end of the task. */
  nuGfxTaskStart(gfx_glist,
                 (s32)(glistp - gfx_glist) * sizeof(Gfx),
                 NU_GFX_UCODE_F3DEX, NU_SC_SWAPBUFFER);
}

// Vertex: xyz, uv, rgba
static Vtx quad_vtx[] = {
    {-16, 16, -5, 0, 0 << 6, 0 << 6, 0x00, 0xff, 0x00, 0xff},
    {16, 16, -5, 0, 31 << 6, 0 << 6, 0x00, 0x00, 0x00, 0xff},
    {16, -16, -5, 0, 31 << 6, 31 << 6, 0x00, 0x00, 0xff, 0xff},
    {-16, -16, -5, 0, 0 << 6, 31 << 6, 0xff, 0x00, 0x00, 0xff},
};

static Vtx cursor_vtx[] = {
    // Top Left
    {-20, 20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-16, 20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-16, 18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-18, 18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-18, 16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-20, 16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    // Top Right
    {20, 20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {16, 20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {16, 18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {18, 18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {18, 16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {20, 16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    // Bottom Left
    {-20, -20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-16, -20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-16, -18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-18, -18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-18, -16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {-20, -16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    // Bottom Right
    {20, -20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {16, -20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {16, -18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {18, -18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {18, -16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
    {20, -16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff},
};

/* Draw a square  */
void shadetri(Matrices *matrices, int type)
{
  glistp = apply_matrices(glistp, matrices);

  gSPVertex(glistp++, &(quad_vtx[0]), 4, 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++, G_CYC_1CYCLE);

  // Set Texture
  /* Enable texture, set scaling parameters */
  gSPTexture(glistp++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);

  /* Specify back surface culling */
  gSPSetGeometryMode(glistp++, G_CULL_BACK);

  /* Switch to combine mode using texture color */
  gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);

  /* Load texture */
  PalPixel *img = 0;
  switch (type)
  {
  case 0b000: // blue-stripes-squid
    img = &_pp_table_sq_bl_st_32x32_CI_4b[0];
    break;

  case 0b001: // blue-stripes-slug
    img = &_pp_table_sl_bl_st_32x32_CI_4b[0];
    break;

  case 0b010: // blue-dots-squid
    img = &_pp_table_sq_bl_dt_32x32_CI_4b[0];
    break;

  case 0b011: // blue-dots-slug
    img = &_pp_table_sl_bl_dt_32x32_CI_4b[0];
    break;

  case 0b100: // orange-stripes-squid
    img = &_pp_table_sq_or_st_32x32_CI_4b[0];
    break;

  case 0b101: // orange-stripes-slug
    img = &_pp_table_sl_or_st_32x32_CI_4b[0];
    break;

  case 0b110: // orange-dots-squid
    img = &_pp_table_sq_or_dt_32x32_CI_4b[0];
    break;

  case 0b111: // orange-dots-slug
    img = &_pp_table_sl_or_dt_32x32_CI_4b[0];
    break;

  case 8:
    img = &_pp_table_dice_sq_32x32_CI_4b[0];
    break;

  case 9:
    img = &_pp_table_dice_sl_32x32_CI_4b[0];
    break;

  case 10:
    img = &_pp_table_dice_st_32x32_CI_4b[0];
    break;

  case 11:
    img = &_pp_table_dice_dt_32x32_CI_4b[0];
    break;

  case 12:
    img = &_pp_table_dice_bl_32x32_CI_4b[0];
    break;

  case 13:
    img = &_pp_table_dice_or_32x32_CI_4b[0];
    break;

  case 14:
    img = &_pp_table_dice_rb_32x32_CI_4b[0];
    break;

  case 15:
    img = &_pp_table_dice_rw_32x32_CI_4b[0];
    break;

  case 16:
    img = &_pp_table_dice_yb_32x32_CI_4b[0];
    break;

  case 17:
    img = &_pp_table_dice_yw_32x32_CI_4b[0];
    break;

  case 18:
    img = &_pp_table_dice_bb_32x32_CI_4b[0];
    break;

  case 19:
    img = &_pp_table_dice_bw_32x32_CI_4b[0];
    break;
  }

  gDPLoadTextureBlock_4b(glistp++,
                         img->pixel.p4,           /* Pointer to texture image */
                         G_IM_FMT_CI,             /* Texel format */
                         32, 32,                  /* Image width and height */
                         0,                       /* LUT (palette) index */
                         G_TX_WRAP, G_TX_WRAP,    /* Clamp, wrap, mirror frag in s direction */
                         5, 5,                    /* s, t masks */
                         G_TX_NOLOD, G_TX_NOLOD); /* Shift (not shifted here) */

  /* Texture perspective correction is turned on during mapping */
  gDPSetTexturePersp(glistp++, G_TP_PERSP);
  /* Set texture filter */
  gDPSetTextureFilter(glistp++, G_TF_BILERP);
  gDPSetTextureConvert(glistp++, G_TC_FILT);
  /* This can be ignored until LOD or detail texture is explained */
  gDPSetTextureLOD(glistp++, G_TL_TILE);
  gDPSetTextureDetail(glistp++, G_TD_CLAMP);

  /* Texture palette */
  gDPSetTextureLUT(glistp++, G_TT_RGBA16);
  gDPLoadTLUT_pal16(glistp++, 0, img->ppal);

  gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

  gSPClearGeometryMode(glistp++, 0xFFFFFFFF);
  gSPSetGeometryMode(glistp++, G_SHADE | G_SHADING_SMOOTH);

  gSP2Triangles(glistp++, 0, 1, 2, 0, 0, 2, 3, 0);
}

u32 renderCards(Cards *cards, u32 id)
{
  f32 fr = 360.0f / (float)cards->count;
  f32 fi = 0.0f;

  for (u32 i = 0; i < cards->count; i++, fi += 1.0f)
  {
    u32 j = id + i;
    set_card_matrices(&graphics.matrices[j], 100.0f, fr * fi);
    shadetri(&graphics.matrices[j], cards->gfx_ids[i] & 7);
  }

  return id + cards->count;
}

u32 renderDice(Dice *dice, u32 id)
{
  set_dice_matrices(&graphics.matrices[id], -20.0f, 20.0f, 0.8f);
  shadetri(&graphics.matrices[id], 8 + dice->gfx_ids[0]);
  id++;

  set_dice_matrices(&graphics.matrices[id], 20.0f, 20.0f, 0.8f);
  shadetri(&graphics.matrices[id], 10 + dice->gfx_ids[1]);
  id++;

  set_dice_matrices(&graphics.matrices[id], -20.0f, -20.0f, 0.8f);
  shadetri(&graphics.matrices[id], 12 + dice->gfx_ids[2]);
  id++;

  set_dice_matrices(&graphics.matrices[id], 20.0f, -20.0f, 0.8f);
  shadetri(&graphics.matrices[id], 14 + dice->gfx_ids[3]);
  id++;

  return id;
}

// Render cursor
void renderCursor(Matrices *m)
{
  glistp = apply_matrices(glistp, m);

  gSPVertex(glistp++, &(cursor_vtx[0]), 24, 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++, G_CYC_1CYCLE);

  gSPTexture(glistp++, 0, 0, 0, 0, G_OFF);
  gDPSetCombineMode(glistp++, G_CC_SHADE, G_CC_SHADE);

  gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gSPClearGeometryMode(glistp++, 0xFFFFFFFF);
  gSPSetGeometryMode(glistp++, G_SHADE | G_SHADING_SMOOTH);

  // Top Left
  gSP2Triangles(glistp++, 0, 1, 2, 0, 0, 2, 3, 0);
  gSP2Triangles(glistp++, 0, 3, 4, 0, 0, 4, 5, 0);
  // Top Right
  gSP2Triangles(glistp++, 6, 8, 7, 0, 6, 9, 8, 0);
  gSP2Triangles(glistp++, 6, 10, 9, 0, 6, 11, 10, 0);
  // Bottom Left
  gSP2Triangles(glistp++, 12, 14, 13, 0, 12, 15, 14, 0);
  gSP2Triangles(glistp++, 12, 16, 15, 0, 12, 17, 16, 0);
  // Bottom Right
  gSP2Triangles(glistp++, 18, 19, 20, 0, 18, 20, 21, 0);
  gSP2Triangles(glistp++, 18, 21, 22, 0, 18, 22, 23, 0);
}
