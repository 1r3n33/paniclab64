#include "story.h"
#include "init.h"
#include "fonts.h"

void render_story()
{
    Gfx *gfx = gfxBegin();

    gfx = gfxClearCfb(gfx, GPACK_RGBA5551(0x70, 0x70, 0xC0, 0xFF), G_MAXFBZ);

    gfx = render_string(gfx, "Room 1", 0, -15.0f, 80.0f);
    gfx = render_string(gfx, "Meet Sluggy", 16, -30.0f, 0.0f);

    gfxEnd(gfx);
}
