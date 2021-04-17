#include <nusys.h>
#include "audio/audio.h"
#include "controls/controls.h"
#include "game/menu.h"
#include "game/story.h"
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
        audio_play_sfx(FX_MENU_TICK);
    }
}

void titlescreen_down()
{
    if (titlescreen_selection == 0)
    {
        titlescreen_selection = 1;
        audio_play_sfx(FX_MENU_TICK);
    }
}

void titlescreen_loop(int pendingGfx)
{
    controls_update();
    NUContData *controller = controls_get(0);

    if (controller->trigger & START_BUTTON || controller->trigger & A_BUTTON)
    {
        audio_play_sfx(FX_MENU_SELECT);

        if (titlescreen_selection == 0)
        {
            story_init();
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
