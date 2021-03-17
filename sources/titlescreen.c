#include <nusys.h>
#include "controls/controls.h"
#include "game/menu.h"
#include "graphics/graphics.h"
#include "graphics/titlescreen.h"
#include "menu.h"
#include "story.h"
#include "titlescreen.h"

u32 titlescreen_selection = 0;

void titlescreen_up()
{
    if (titlescreen_selection == 1)
    {
        titlescreen_selection = 0;
    }
}

void titlescreen_down()
{
    if (titlescreen_selection == 0)
    {
        titlescreen_selection = 1;
    }
}

void titlescreen_loop(int pendingGfx)
{
    controls_update();
    NUContData *controller = controls_get(0);

    if (controller->trigger & START_BUTTON || controller->trigger & A_BUTTON)
    {
        if (titlescreen_selection == 0)
        {
            nuGfxFuncSet((NUGfxFunc)story_loop);
        }
        else if (titlescreen_selection == 1)
        {
            init_menu();
            nuGfxFuncSet((NUGfxFunc)menu_loop);
        }
    }

    if (controller->trigger & U_JPAD || controller->stick_y > 50)
    {
        titlescreen_up();
    }

    if (controller->trigger & D_JPAD || controller->stick_y < -50)
    {
        titlescreen_down();
    }

    graphics.selection = titlescreen_selection;

    if (pendingGfx < 1)
    {
        render_titlescreen();
    }
}
