#include <assert.h>
#include <nusys.h>
#include "init.h"

/*
  The viewport structure
  The conversion from (-1,-1,-1)-(1,1,1).  The decimal part is 2-bit.
 */
static Vp vp = {
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* The scale factor  */
    SCREEN_WD * 2, SCREEN_HT * 2, G_MAXZ / 2, 0, /* Move  */
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

Gfx gfx_glist[GFX_GLIST_LEN];

/*----------------------------------------------------------------------------
  The initialization of RSP/RDP
----------------------------------------------------------------------------*/
Gfx *gfxBegin(void)
{
    Gfx *gfx = gfx_glist;

    /* Setting the RSP segment register  */
    gSPSegment(gfx++, 0, 0x0); /* For the CPU virtual address  */

    /* Setting RSP */
    gSPDisplayList(gfx++, OS_K0_TO_PHYSICAL(setup_rspstate));

    /* Setting RDP  */
    gSPDisplayList(gfx++, OS_K0_TO_PHYSICAL(setup_rdpstate));

    return gfx;
}

void gfxEnd(Gfx *gfx)
{
    /* End the construction of the display list  */
    gDPFullSync(gfx++);
    gSPEndDisplayList(gfx++);

    /* Check if all are put in the array  */
    assert(gfx - gfx_glist < GFX_GLIST_LEN);

    /* Activate the RSP task. Switch display buffers at the end of the task. */
    nuGfxTaskStart(gfx_glist,
                   (s32)(gfx - gfx_glist) * sizeof(Gfx),
                   NU_GFX_UCODE_F3DEX, NU_SC_SWAPBUFFER);
}

/*----------------------------------------------------------------------------
  gfxClearCfb

  Setting addresses of the frame buffer/Z-buffer and clear them

  Using nuGfxZBuffer (the address of the Z-buffer) and nuGfxCfb_ptr (the
  address of the frame buffer) which are global variables of NuSYSTEM.
----------------------------------------------------------------------------*/
Gfx *gfxClearCfb(Gfx *gfx, u16 rgba, u16 z)
{
    gDPSetCycleType(
        gfx++,
        G_CYC_FILL);

    // Clear the Z-buffer
    gDPSetDepthImage(
        gfx++,
        OS_K0_TO_PHYSICAL(nuGfxZBuffer));

    gDPSetColorImage(
        gfx++,
        G_IM_FMT_RGBA,
        G_IM_SIZ_16b,
        SCREEN_WD,
        OS_K0_TO_PHYSICAL(nuGfxZBuffer));

    gDPSetFillColor(
        gfx++,
        (GPACK_ZDZ(z, 0) << 16 | GPACK_ZDZ(z, 0)));

    gDPFillRectangle(
        gfx++,
        0,
        0,
        SCREEN_WD - 1,
        SCREEN_HT - 1);

    gDPPipeSync(gfx++);

    // Clear the frame buffer
    gDPSetColorImage(
        gfx++,
        G_IM_FMT_RGBA,
        G_IM_SIZ_16b,
        SCREEN_WD,
        osVirtualToPhysical(nuGfxCfb_ptr));

    gDPSetFillColor(
        gfx++,
        (rgba << 16 | rgba));

    gDPFillRectangle(
        gfx++,
        0,
        0,
        SCREEN_WD - 1,
        SCREEN_HT - 1);

    gDPPipeSync(gfx++);
}
