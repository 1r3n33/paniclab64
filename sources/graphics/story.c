#include "story.h"
#include "init.h"

void render_story()
{
    Gfx *gfx = gfxBegin();

    gfx = gfxClearCfb(gfx, GPACK_RGBA5551(0x70, 0x70, 0xC0, 0xFF), G_MAXFBZ);

    gfxEnd(gfx);
}
