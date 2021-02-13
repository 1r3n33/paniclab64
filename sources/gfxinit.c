#include <nusys.h>
#include "graphic.h"

/*
  The viewport structure
  The conversion from (-1,-1,-1)-(1,1,1).  The decimal part is 2-bit.
 */
static Vp vp = {
    SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* The scale factor  */
    SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* Move  */
};

// RDP Initialization
Gfx setup_rdpstate[] = {
  gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
  gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
  gsDPSetColorDither(G_CD_BAYER),
  gsSPEndDisplayList(),
};

// RSP Initialization
Gfx setup_rspstate[] = {
  gsSPViewport(&vp),
  gsSPClearGeometryMode(0xFFFFFFFF),
  gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK),
  gsSPTexture(0, 0, 0, 0, G_OFF),
  gsSPEndDisplayList(),
};
