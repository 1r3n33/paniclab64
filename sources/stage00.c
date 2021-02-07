/*
   stage00.c

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "graphic.h"

#include "../assets/graphics/sq_bl_st_32x32_CI_4b.h"
#include "../assets/graphics/sq_or_st_32x32_CI_4b.h"
#include "../assets/graphics/sq_bl_dt_32x32_CI_4b.h"
#include "../assets/graphics/sq_or_dt_32x32_CI_4b.h"

void applyMatrices(Matrices* matrices);

void shadetri(Matrices* matrices, int type);

/* Make the display list and activate the task. */

void makeDL00(void)
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

  for (int i = 0; i<MATRICES_MAX_LEN; i++)
  {
    guTranslate(&gfx_matrices[i].translation, 0.0F, 100.0F, 0.0F);
    guRotate(&gfx_matrices[i].rotation, (360.0F/(float)MATRICES_MAX_LEN)*(float)i, 0.0F, 0.0F, 1.0F);
    guScale(&gfx_matrices[i].scale, 0.0F, 1.0F, 1.0F);

    /* Draw a square  */
    shadetri(&gfx_matrices[i], i&3);
  }

  /* End the construction of the display list  */
  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  /* Check if all are put in the array  */
  assert(glistp - gfx_glist < GFX_GLIST_LEN);

  /* Activate the RSP task.  Switch display buffers at the end of the task. */
  nuGfxTaskStart(gfx_glist,
		 (s32)(glistp - gfx_glist) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX , NU_SC_SWAPBUFFER);
}

/* The vertex coordinate  */
static Vtx shade_vtx[] =  {
        {        -16,  16, -5, 0, 31<<6,  0<<6, 0x00, 0xff, 0x00, 0xff	},
        {         16,  16, -5, 0,  0<<0,  0<<6, 0x00, 0x00, 0x00, 0xff	},
        {         16, -16, -5, 0,  0<<6, 31<<6, 0x00, 0x00, 0xff, 0xff	},
        {        -16, -16, -5, 0, 31<<6, 31<<6, 0xff, 0x00, 0x00, 0xff	},
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
}

/* Draw a square  */
void shadetri(Matrices* matrices, int type)
{
  applyMatrices(matrices);

  gSPVertex(glistp++,&(shade_vtx[0]),4, 0);

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
