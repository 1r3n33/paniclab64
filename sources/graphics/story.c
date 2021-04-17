#include "init.h"
#include "fonts.h"
#include "graphics.h"
#include "projection.h"
#include "story.h"

void render_story()
{
    Gfx *gfx = gfxBegin();

    gfx = gfxClearCfb(gfx, GPACK_RGBA5551(0xE8, 0xA8, 0xB8, 0xFF), G_MAXFBZ);

    gfx = apply_projection(gfx, (f32)SCREEN_WD, (f32)SCREEN_HT);

    gfx = render_string(gfx, graphics.text[0], 10, -20.0f, 80.0f);
    gfx = render_string(gfx, graphics.text[1], 20, -20.0f, 60.0f);

    gfx = render_string(gfx, graphics.text[2], 130, -100.0f, -100.0f);
    gfx = render_string(gfx, graphics.text[3], 140, 80.0f, -100.0f);

    gfxEnd(gfx);
}
