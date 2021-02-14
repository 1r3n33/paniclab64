#include <assert.h>
#include <nusys.h>
#include "game.h"
#include "graphic.h"

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

void applyMatrices(Matrices* matrices);

void shadetri(Matrices* matrices, int type);

void renderCursor(Matrices* m);

/* Make the display list and activate the task. */

void makeDL00(Game* game)
{
  /* Specify the display list buffer  */
  glistp = gfx_glist;

  /*  The initialization of RCP  */
  gfxRCPInit();

  /* Clear the frame buffer and the Z-buffer  */
  gfxClearCfb();

  // Compute projection matrix
  guOrtho(&gfx_dynamic.projection,
    -(float)SCREEN_WD/2.0F, (float)SCREEN_WD/2.0F,
    -(float)SCREEN_HT/2.0F, (float)SCREEN_HT/2.0F,
    1.0F, 10.0F, 1.0F);

  // Set projection matrix
  gSPMatrix(
    glistp++,
    OS_K0_TO_PHYSICAL(&gfx_dynamic.projection),
    G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

  // Draw cards circle
  for (u32 i = 0; i<game->cards.count; i++)
  {
    guTranslate(&gfx_matrices[i].translation, 0.0F, 100.0F, 0.0F);
    guRotate(&gfx_matrices[i].rotation, (360.0F/(float)game->cards.count)*(float)i, 0.0F, 0.0F, 1.0F);
    guScale(&gfx_matrices[i].scale, 1.0F, 1.0F, 1.0F);

    shadetri(&gfx_matrices[i], game->cards.gfx_ids[i]&7);
  }

  // Draw dice
  for (u32 j=0; j<game->dice.count; j++)
  {
    u32 k = game->cards.count+j;
    guTranslate(&gfx_matrices[k].translation, -40.0F+((float)j*40.0F), 0.0F, 0.0F);
    guRotate(&gfx_matrices[k].rotation, 0.0F, 0.0F, 0.0F, 1.0F);
    guScale(&gfx_matrices[k].scale, 0.8F, 0.8F, 0.8F);

    shadetri(&gfx_matrices[k], 8+((j*2)+game->dice.gfx_ids[j]));
  }

  // Draw cursor
  renderCursor(&gfx_matrices[game->cursor.cur_pos]);

  /* End the construction of the display list  */
  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  /* Check if all are put in the array  */
  assert(glistp - gfx_glist < GFX_GLIST_LEN);

  /* Activate the RSP task. Switch display buffers at the end of the task. */
  nuGfxTaskStart(gfx_glist,
     (s32)(glistp - gfx_glist) * sizeof (Gfx),
     NU_GFX_UCODE_F3DEX , NU_SC_SWAPBUFFER);
}

// Vertex: xyz, uv, rgba
static Vtx quad_vtx[] =  {
  { -16,  16, -5, 0,  0<<6,  0<<6, 0x00, 0xff, 0x00, 0xff },
  {  16,  16, -5, 0, 31<<6,  0<<6, 0x00, 0x00, 0x00, 0xff },
  {  16, -16, -5, 0, 31<<6, 31<<6, 0x00, 0x00, 0xff, 0xff },
  { -16, -16, -5, 0,  0<<6, 31<<6, 0xff, 0x00, 0x00, 0xff },
};

static Vtx cursor_vtx[] =  {
  // Top Left
  { -20,  20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -16,  20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -16,  18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -18,  18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -18,  16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -20,  16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  // Top Right
  {  20,  20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  16,  20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  16,  18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  18,  18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  18,  16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  20,  16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  // Bottom Left
  { -20, -20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -16, -20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -16, -18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -18, -18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -18, -16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  { -20, -16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  // Bottom Right
  {  20, -20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  16, -20, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  16, -18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  18, -18, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  18, -16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
  {  20, -16, -4, 0, 0, 0, 0xff, 0x00, 0x00, 0xff },
};

void applyMatrices(Matrices* matrices)
{
  gSPMatrix(
    glistp++,
    OS_K0_TO_PHYSICAL(&(matrices->rotation)),
    G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

  gSPMatrix(
    glistp++,
    OS_K0_TO_PHYSICAL(&(matrices->translation)),
    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

  gSPMatrix(
    glistp++,
    OS_K0_TO_PHYSICAL(&(matrices->scale)),
    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
}

/* Draw a square  */
void shadetri(Matrices* matrices, int type)
{
  applyMatrices(matrices);

  gSPVertex(glistp++,&(quad_vtx[0]),4, 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++,G_CYC_1CYCLE);

  // Set Texture
  /* Enable texture, set scaling parameters */
  gSPTexture(glistp++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);

  /* Specify back surface culling */
  gSPSetGeometryMode(glistp++, G_CULL_BACK);

  /* Switch to combine mode using texture color */
  gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);

  /* Load texture */
  PalPixel * img = 0;
  switch (type)
  {
  case 0:
    img = &_pp_table_sq_bl_st_32x32_CI_4b[0];
    break;

  case 1:
    img = &_pp_table_sq_or_st_32x32_CI_4b[0];
    break;

  case 2:
    img = &_pp_table_sq_bl_dt_32x32_CI_4b[0];
    break;

  case 3:
    img = &_pp_table_sq_or_dt_32x32_CI_4b[0];
    break;

  case 4:
    img = &_pp_table_sl_bl_st_32x32_CI_4b[0];
    break;

  case 5:
    img = &_pp_table_sl_or_st_32x32_CI_4b[0];
    break;

  case 6:
    img = &_pp_table_sl_bl_dt_32x32_CI_4b[0];
    break;

  case 7:
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
  }

  gDPLoadTextureBlock_4b(glistp++,
                         img->pixel.p4,            /* Pointer to texture image */
                         G_IM_FMT_CI,              /* Texel format */
                         32, 32,                   /* Image width and height */
                         0,                        /* LUT (palette) index */
                         G_TX_WRAP, G_TX_WRAP,     /* Clamp, wrap, mirror frag in s direction */
                         5, 5,                     /* s, t masks */
                         G_TX_NOLOD, G_TX_NOLOD);  /* Shift (not shifted here) */

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

  gDPSetRenderMode(glistp++,G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

  gSPClearGeometryMode(glistp++,0xFFFFFFFF);
  gSPSetGeometryMode(glistp++,G_SHADE| G_SHADING_SMOOTH);

  gSP2Triangles(glistp++,0,1,2,0,0,2,3,0);
}

// Render cursor
void renderCursor(Matrices* m)
{
  applyMatrices(m);

  gSPVertex(glistp++, &(cursor_vtx[0]), 24, 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++,G_CYC_1CYCLE);

  gSPTexture(glistp++, 0, 0, 0, 0, G_OFF);
  gDPSetCombineMode(glistp++, G_CC_SHADE, G_CC_SHADE);

  gDPSetRenderMode(glistp++,G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gSPClearGeometryMode(glistp++,0xFFFFFFFF);
  gSPSetGeometryMode(glistp++,G_SHADE| G_SHADING_SMOOTH);

  // Top Left
  gSP2Triangles(glistp++, 0, 1, 2, 0, 0, 2, 3, 0);
  gSP2Triangles(glistp++, 0, 3, 4, 0, 0, 4, 5, 0);
  // Top Right
  gSP2Triangles(glistp++, 6,  8, 7, 0, 6,  9, 8,  0);
  gSP2Triangles(glistp++, 6, 10, 9, 0, 6, 11, 10, 0);
  // Bottom Left
  gSP2Triangles(glistp++, 12, 14, 13, 0, 12, 15, 14, 0);
  gSP2Triangles(glistp++, 12, 16, 15, 0, 12, 17, 16, 0);
  // Bottom Right
  gSP2Triangles(glistp++, 18, 19, 20, 0, 18, 20, 21, 0);
  gSP2Triangles(glistp++, 18, 21, 22, 0, 18, 22, 23, 0);
}
