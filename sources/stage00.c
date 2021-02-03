/*
   stage00.c

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "graphic.h"

void applyMatrices(Matrices* matrices);

void shadetri(Matrices* matrices);

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
    guTranslate(&gfx_matrices[i].translation, 100.0F, 0.0F, 0.0F);
    guRotate(&gfx_matrices[i].rotation, (360.0F/(float)MATRICES_MAX_LEN)*(float)i, 0.0F, 0.0F, 1.0F);
    guScale(&gfx_matrices[i].scale, 0.0F, 1.0F, 1.0F);

    /* Draw a square  */
    shadetri(&gfx_matrices[i]);
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
        {        -16,  16, -5, 0, 0, 0, 0, 0xff, 0, 0xff	},
        {         16,  16, -5, 0, 0, 0, 0, 0, 0, 0xff	},
        {         16, -16, -5, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -16, -16, -5, 0, 0, 0, 0xff, 0, 0, 0xff	},
};

void applyMatrices(Matrices* matrices)
{
  gSPMatrix(
    glistp++,
    OS_K0_TO_PHYSICAL(&(matrices->rotation)),
		G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

#if 1
  gSPMatrix(
    glistp++,
    OS_K0_TO_PHYSICAL(&(matrices->translation)),
		G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
#endif
}

/* Draw a square  */
void shadetri(Matrices* matrices)
{
  applyMatrices(matrices);

  gSPVertex(glistp++,&(shade_vtx[0]),4, 0);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++,G_CYC_1CYCLE);
  gDPSetRenderMode(glistp++,G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  gSPClearGeometryMode(glistp++,0xFFFFFFFF);
  gSPSetGeometryMode(glistp++,G_SHADE| G_SHADING_SMOOTH);

  gSP2Triangles(glistp++,0,1,2,0,0,2,3,0);
}
