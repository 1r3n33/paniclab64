#include <nusys.h>
#include "audio/audio.h"
#include "controls/controls.h"
#include "game.h"
#include "game/game.h"
#include "game/story.h"
#include "graphics/graphics.h"
#include "graphics/story.h"
#include "story.h"
#include "titlescreen.h"

void story_init_level(u32 level)
{
    switch (level)
    {
    case 0:
        init_game(1, SETTINGS_FLAG_SHAPE_0);
        break;

    case 1:
        init_game(1, SETTINGS_FLAG_SHAPE_ALL);
        break;

    case 2:
        init_game(1, SETTINGS_FLAG_SHAPE_ALL | SETTINGS_FLAG_MUTATION_0);
        break;

    default:
        init_game(1, SETTINGS_FLAG_MUTATION_ALL | SETTINGS_FLAG_AIRVENTS | SETTINGS_FLAG_SHAPE_ALL);
        break;
    }

    shuffle_game();
    game_loop_init(3, (NUGfxFunc)story_loop);
    nuGfxFuncSet((NUGfxFunc)game_loop);
}

void story_loop(int pending_gfx)
{
    controls_update();
    NUContData *controller = controls_get(0);

    if (controller->trigger & A_BUTTON)
    {
        s32 next = story_action();
        if (next < 0)
        {
            audio_play_sfx(FX_MENU_SELECT);
            nuGfxFuncSet((NUGfxFunc)titlescreen_loop);
        }
        else if (next > 0)
        {
            audio_play_sfx(FX_MENU_SELECT);
            story_init_level(story_get_current_level());
        }
    }

    if (controller->trigger & U_JPAD || controller->stick_y > 50)
    {
        u32 ok = story_up();
        if (ok)
        {
            audio_play_sfx(FX_MENU_TICK);
        }
    }

    if (controller->trigger & D_JPAD || controller->stick_y < -50)
    {
        u32 ok = story_down();
        if (ok)
        {
            audio_play_sfx(FX_MENU_TICK);
        }
    }

    if (controller->trigger & L_JPAD || controller->stick_x < -50)
    {
        u32 ok = story_left();
        if (ok)
        {
            audio_play_sfx(FX_MENU_TICK);
        }
    }

    if (controller->trigger & R_JPAD || controller->stick_x > 50)
    {
        u32 ok = story_right();
        if (ok)
        {
            audio_play_sfx(FX_MENU_TICK);
        }
    }

    graphics.selection = story_to_gfx(graphics.text);

    if (pending_gfx < 1)
    {
        render_story();
    }
}
