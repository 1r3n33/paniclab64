#ifndef INIT_H
#define INIT_H

#include <nusys.h>

/* The screen size  */
#define SCREEN_HT 240
#define SCREEN_WD 320

/* The maximum length of the display list of one task  */
#define GFX_GLIST_LEN 2048

Gfx *gfxBegin(void);
void gfxEnd(Gfx *gfx);

Gfx *gfxClearCfb(Gfx *gfx, u16 rgba, u16 z);

#endif // INIT_H
