#include <assert.h>
#include <nusys.h>
#include "game/game.h"
#include "graphic.h"
#include "graphics/graphics.h"

void renderQuad(Matrices *mtx, u32 tex_id);

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

  glistp = apply_projection(glistp, (f32)SCREEN_WD, (f32)SCREEN_HT);

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
void renderQuad(Matrices *mtx, u32 tex_id)
{
  glistp = apply_matrices(glistp, mtx);

  gSPVertex(glistp++, &(quad_vtx[0]), 4, 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++, G_CYC_1CYCLE);

  /* Specify back surface culling */
  gSPSetGeometryMode(glistp++, G_CULL_BACK);

  glistp = apply_texture(glistp, tex_id);

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
    renderQuad(&graphics.matrices[j], cards->gfx_ids[i]);
  }

  return id + cards->count;
}

u32 renderDice(Dice *dice, u32 id)
{
  set_dice_matrices(&graphics.matrices[id], -20.0f, 20.0f, 0.8f);
  renderQuad(&graphics.matrices[id], 15 + dice->gfx_ids[0]);
  id++;

  set_dice_matrices(&graphics.matrices[id], 20.0f, 20.0f, 0.8f);
  renderQuad(&graphics.matrices[id], 17 + dice->gfx_ids[1]);
  id++;

  set_dice_matrices(&graphics.matrices[id], -20.0f, -20.0f, 0.8f);
  renderQuad(&graphics.matrices[id], 19 + dice->gfx_ids[2]);
  id++;

  set_dice_matrices(&graphics.matrices[id], 20.0f, -20.0f, 0.8f);
  renderQuad(&graphics.matrices[id], 21 + dice->gfx_ids[3]);
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
