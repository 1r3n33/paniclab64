#include <nusys.h>
#include "game/game.h"
#include "graphics/graphics.h"

Gfx *renderQuad(Gfx *gfx, Matrices *mtx, u32 tex_id);

Gfx *renderDice(Gfx *gfx, Dice *dice, u32 id);

Gfx *renderCursor(Gfx *gfx, u32 cursor_id, Matrices *m);

Gfx *renderCards(Gfx *gfx, u32 card_count, u32 *card_gfx_ids, u32 id)
{
  f32 fr = 360.0f / (float)card_count;
  f32 fi = 0.0f;

  for (u32 i = 0; i < card_count; i++, fi += 1.0f)
  {
    u32 j = id + i;
    set_card_matrices(&graphics.matrices[j], 100.0f, fr * fi);
    gfx = renderQuad(gfx, &graphics.matrices[j], card_gfx_ids[i]);
  }

  return gfx;
}

/* Make the display list and activate the task. */
void render_game(Game *game)
{
  /*  The initialization of RCP  */
  Gfx *gfx = gfxBegin();

  /* Clear the frame buffer and the Z-buffer  */
  gfx = gfxClearCfb(gfx);

  gfx = apply_projection(gfx, (f32)SCREEN_WD, (f32)SCREEN_HT);

  gfx = renderCards(gfx, graphics.card_count, graphics.card_gfx_ids, 0);
  gfx = renderDice(gfx, &game->dice, 32);

  // Render cursors
  gfx = renderCursor(gfx, 0, &graphics.matrices[graphics.cursors[0]]);
  gfx = renderCursor(gfx, 1, &graphics.matrices[graphics.cursors[1]]);

  // Render scores
  gfx = render_string(gfx, graphics.text[0], 0, -150.0f, 100.0f);
  gfx = render_string(gfx, graphics.text[1], 8, 100.0f, 100.0f);

  gfxEnd(gfx);
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
    {-20, 20, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-16, 20, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-16, 18, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-18, 18, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-18, 16, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-20, 16, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    // Top Right
    {20, 20, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {16, 20, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {16, 18, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {18, 18, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {18, 16, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {20, 16, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    // Bottom Left
    {-20, -20, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-16, -20, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-16, -18, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-18, -18, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-18, -16, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {-20, -16, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    // Bottom Right
    {20, -20, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {16, -20, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {16, -18, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {18, -18, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {18, -16, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
    {20, -16, -4, 0, 0, 0, 0x00, 0x00, 0x00, 0xff},
};

/* Draw a square  */
Gfx *renderQuad(Gfx *gfx, Matrices *mtx, u32 tex_id)
{
  gfx = apply_matrices(gfx, mtx);

  gSPVertex(gfx++, &(quad_vtx[0]), 4, 0);

  gDPPipeSync(gfx++);
  gDPSetCycleType(gfx++, G_CYC_1CYCLE);

  /* Specify back surface culling */
  gSPSetGeometryMode(gfx++, G_CULL_BACK);

  gfx = apply_texture(gfx, tex_id);

  gDPSetRenderMode(gfx++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

  gSPClearGeometryMode(gfx++, 0xFFFFFFFF);
  gSPSetGeometryMode(gfx++, G_SHADE | G_SHADING_SMOOTH);

  gSP2Triangles(gfx++, 0, 1, 2, 0, 0, 2, 3, 0);

  return gfx;
}

Gfx *renderDice(Gfx *gfx, Dice *dice, u32 id)
{
  set_dice_matrices(&graphics.matrices[id], -20.0f, 20.0f, 0.8f);
  gfx = renderQuad(gfx, &graphics.matrices[id], 15 + dice->gfx_ids[0]);
  id++;

  set_dice_matrices(&graphics.matrices[id], 20.0f, 20.0f, 0.8f);
  gfx = renderQuad(gfx, &graphics.matrices[id], 17 + dice->gfx_ids[1]);
  id++;

  set_dice_matrices(&graphics.matrices[id], -20.0f, -20.0f, 0.8f);
  gfx = renderQuad(gfx, &graphics.matrices[id], 19 + dice->gfx_ids[2]);
  id++;

  set_dice_matrices(&graphics.matrices[id], 20.0f, -20.0f, 0.8f);
  gfx = renderQuad(gfx, &graphics.matrices[id], 21 + dice->gfx_ids[3]);
  id++;

  return gfx;
}

// Render cursor
u32 cursor_colors[4][4] = {
    {0xff, 0x00, 0x00, 0xff},
    {0x00, 0x00, 0xff, 0xff},
    {0x00, 0x00, 0x00, 0xff},
    {0x00, 0x00, 0x00, 0xff},
};

Gfx *renderCursor(Gfx *gfx, u32 cursor_id, Matrices *m)
{
  gfx = apply_matrices(gfx, m);

  gSPVertex(gfx++, &(cursor_vtx[0]), 24, 0);

  gDPPipeSync(gfx++);
  gDPSetCycleType(gfx++, G_CYC_1CYCLE);

  gSPTexture(gfx++, 0, 0, 0, 0, G_OFF);
  gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

  gDPSetRenderMode(gfx++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gSPClearGeometryMode(gfx++, 0xFFFFFFFF);

  gDPSetPrimColor(
      gfx++, 0, 0,
      cursor_colors[cursor_id][0], cursor_colors[cursor_id][1], cursor_colors[cursor_id][2], cursor_colors[cursor_id][3]);

  // Top Left
  gSP2Triangles(gfx++, 0, 1, 2, 0, 0, 2, 3, 0);
  gSP2Triangles(gfx++, 0, 3, 4, 0, 0, 4, 5, 0);
  // Top Right
  gSP2Triangles(gfx++, 6, 8, 7, 0, 6, 9, 8, 0);
  gSP2Triangles(gfx++, 6, 10, 9, 0, 6, 11, 10, 0);
  // Bottom Left
  gSP2Triangles(gfx++, 12, 14, 13, 0, 12, 15, 14, 0);
  gSP2Triangles(gfx++, 12, 16, 15, 0, 12, 17, 16, 0);
  // Bottom Right
  gSP2Triangles(gfx++, 18, 19, 20, 0, 18, 20, 21, 0);
  gSP2Triangles(gfx++, 18, 21, 22, 0, 18, 22, 23, 0);

  return gfx;
}
