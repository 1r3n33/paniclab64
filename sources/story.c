#include <nusys.h>
#include "controls/controls.h"
#include "graphics/story.h"
#include "story.h"
#include "titlescreen.h"

void story_loop(int pending_gfx)
{
    controls_update();
    NUContData *controller = controls_get(0);

    if (controller->trigger)
    {
        nuGfxFuncSet((NUGfxFunc)titlescreen_loop);
    }

    if (pending_gfx < 1)
    {
        render_story();
    }
}
