#include "fonts.h"
#include "graphics.h"
#include "init.h"
#include "menu.h"
#include "projection.h"

void render_menu()
{
    Gfx *gfx = gfxBegin();

    gfx = gfxClearCfb(gfx, GPACK_RGBA5551(0x70, 0xC0, 0x70, 0xFF), G_MAXFBZ);
    gfx = apply_projection(gfx, (f32)SCREEN_WD, (f32)SCREEN_HT);

    gfx = render_string(gfx, "Settings", 0, -20.0f, 100.0f);

    gfx = render_string(gfx, graphics.text[0], 10, -50.0f, 60.0f);
    gfx = render_string(gfx, graphics.text[1], 20, 30.0f, 60.0f);

    gfx = render_string(gfx, graphics.text[2], 30, -50.0f, 40.0f);
    gfx = render_string(gfx, graphics.text[3], 40, 30.0f, 40.0f);

    gfx = render_string(gfx, graphics.text[4], 50, -50.0f, 20.0f);
    gfx = render_string(gfx, graphics.text[5], 60, 30.0f, 20.0f);

    gfx = render_string(gfx, graphics.text[6], 70, -50.0f, 0.0f);
    gfx = render_string(gfx, graphics.text[7], 80, 30.0f, 0.0f);

    gfx = render_string(gfx, graphics.text[8], 90, -50.0f, -40.0f);
    gfx = render_string(gfx, graphics.text[9], 100, 30.0f, -40.0f);
    gfx = render_string(gfx, graphics.text[10], 110, -50.0f, -60.0f);
    gfx = render_string(gfx, graphics.text[11], 120, 30.0f, -60.0f);

    gfx = render_string(gfx, graphics.text[12], 130, -100.0f, -100.0f);
    gfx = render_string(gfx, graphics.text[13], 140, 80.0f, -100.0f);

    gfxEnd(gfx);
}
