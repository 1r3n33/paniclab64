#include <nusys.h>
#include "ai/ai.h"
#include "audio/audio.h"
#include "controls/controls.h"
#include "game.h"
#include "game/game.h"
#include "game/menu.h"
#include "graphics/graphics.h"
#include "graphics/menu.h"
#include "menu.h"
#include "titlescreen.h"

void menu_loop(int pendingGfx)
{
    controls_update();
    NUContData *controller = controls_get(0);

    if (controller->trigger & START_BUTTON)
    {
        audio_play_sfx(FX_MENU_SELECT);

        u32 player_count = get_settings_player_count();
        u32 settings_flags = get_settings_flags();
        init_game(player_count, settings_flags);
        shuffle_game();
        ai_init(get_settings(), get_cards(), get_dice(), get_cursors());

        game_loop_init(10, (NUGfxFunc)menu_loop);
        nuGfxFuncSet((NUGfxFunc)game_loop);
    }

    if (controller->trigger & A_BUTTON)
    {
        s32 next = menu_action();
        if (next < 0)
        {
            audio_play_sfx(FX_MENU_SELECT);

            nuGfxFuncSet((NUGfxFunc)titlescreen_loop);
        }
        else if (next > 0)
        {
            audio_play_sfx(FX_MENU_SELECT);

            u32 player_count = get_settings_player_count();
            u32 settings_flags = get_settings_flags();
            init_game(player_count, settings_flags);
            shuffle_game();
            ai_init(get_settings(), get_cards(), get_dice(), get_cursors());

            game_loop_init(10, (NUGfxFunc)menu_loop);
            nuGfxFuncSet((NUGfxFunc)game_loop);
        }
    }

    if (controller->trigger & U_JPAD || controller->stick_y > 50)
    {
        u32 ok = menu_up();
        if (ok)
        {
            audio_play_sfx(FX_MENU_TICK);
        }
    }

    if (controller->trigger & D_JPAD || controller->stick_y < -50)
    {
        u32 ok = menu_down();
        if (ok)
        {
            audio_play_sfx(FX_MENU_TICK);
        }
    }

    if (controller->trigger & L_JPAD || controller->stick_x < -50)
    {
        u32 ok = menu_left();
        if (ok)
        {
            audio_play_sfx(FX_MENU_TICK);
        }
    }

    if (controller->trigger & R_JPAD || controller->stick_x > 50)
    {
        u32 ok = menu_right();
        if (ok)
        {
            audio_play_sfx(FX_MENU_TICK);
        }
    }

    graphics.selection = menu_to_gfx(graphics.text);

    if (pendingGfx < 1)
    {
        render_menu();
    }
}
