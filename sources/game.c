#include <nusys.h>
#include "ai/ai.h"
#include "controls/controls.h"
#include "game.h"
#include "game/game.h"
#include "graphics/game.h"
#include "graphics/graphics.h"
#include "menu.h"

#define LOOP_CONTINUE 0x0
#define LOOP_STOP_WIN 0x1
#define LOOP_STOP_QUIT 0x2

u32 update_player(u32 player_id)
{
    NUContData *controller = ai_is_enabled(player_id)
                                 ? ai_controls_get(player_id)
                                 : controls_get(player_id);

    if (controller->trigger & A_BUTTON)
    {
        u32 solution = get_solution();
        if (cursor_equals(player_id, solution))
        {
            add_to_score(player_id, 100);
            return LOOP_STOP_WIN;
        }
        else
        {
            add_to_score(player_id, -50);
        }
    }

    if (controller->trigger & L_JPAD)
    {
        move_cursor(player_id, 1);
    }

    if (controller->trigger & R_JPAD)
    {
        move_cursor(player_id, -1);
    }

    u32 card_count = get_cards_count();
    s32 index = controls_get_index(player_id, card_count);
    if (index >= 0)
    {
        set_cursor(player_id, index);
    }

    // Shuffle cards
    if (controller->trigger & START_BUTTON)
    {
        return LOOP_STOP_QUIT;
    }

    return LOOP_CONTINUE;
}

u32 game_round_count;
NUGfxFunc game_next_loop;

void game_loop_init(u32 round_count, NUGfxFunc next_loop)
{
    game_round_count = round_count;
    game_next_loop = next_loop;
}

void game_loop(int pendingGfx)
{
    controls_update();

    u32 status = 0;
    status |= update_player(0);
    status |= update_player(1);
    status |= update_player(2);
    status |= update_player(3);

    if (status & LOOP_STOP_WIN)
    {
        game_round_count--;
        if (game_round_count > 0)
        {
            reset_cursors();
            shuffle_game();
            ai_init(get_settings(), get_cards(), get_dice(), get_cursors());
        }
        else
        {
            nuGfxFuncSet(game_next_loop);
        }
    }
    else if (status & LOOP_STOP_QUIT)
    {
        nuGfxFuncSet(game_next_loop);
    }
    else
    {
        // Map game data to graphics data
        graphics.card_count = cards_to_gfx(graphics.card_gfx_ids);
        graphics.dice_count = dice_to_gfx(graphics.dice_gfx_ids);
        graphics.cursor_count = cursors_to_gfx(graphics.cursors);
        score_to_string(0, graphics.text[0]);
        score_to_string(1, graphics.text[1]);
        score_to_string(2, graphics.text[2]);
        score_to_string(3, graphics.text[3]);

        if (pendingGfx < 1)
        {
            render_game();
        }
    }
}
