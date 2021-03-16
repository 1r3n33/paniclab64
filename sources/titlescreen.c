#include <nusys.h>
#include "controls/controls.h"
#include "game/menu.h"
#include "graphics/titlescreen.h"
#include "menu.h"
#include "titlescreen.h"

void titlescreen_loop(int pendingGfx)
{
    controls_update();
    NUContData *controller = controls_get(0);

    if (controller->trigger & START_BUTTON)
    {
        init_menu();
        nuGfxFuncSet((NUGfxFunc)menu_loop);
    }

    if (pendingGfx < 1)
    {
        render_titlescreen();
    }
}
