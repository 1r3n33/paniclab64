#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

/* The screen size  */
#define SCREEN_HT 240
#define SCREEN_WD 320

/* The maximum length of the display list of one task  */
#define GFX_GLIST_LEN 2048

// Matrices max length
#define MATRICES_MAX_LEN 32

/*-------------------------- define structure ------------------------------ */
/* The projection-matrix structure  */
typedef struct {
  Mtx     projection;
} Dynamic;

typedef struct {
  Mtx translation;
  Mtx rotation;
  Mtx scale;
} Matrices;

/*-------------------------------- parameter---------------------------------*/
extern Dynamic  gfx_dynamic;
extern Matrices gfx_matrices[MATRICES_MAX_LEN];
extern Gfx*     glistp;
extern Gfx      gfx_glist[GFX_GLIST_LEN];
/*-------------------------------- function ---------------------------------*/
extern void gfxRCPInit(void);
extern void gfxClearCfb(void);
/*------------------------------- other extern define -----------------------*/
extern Gfx setup_rdpstate[];
extern Gfx setup_rspstate[];

#endif /* _GRAPHIC_H_ */
