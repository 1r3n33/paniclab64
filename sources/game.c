#include <nusys.h>
#include "ai/ai.h"
#include "controls/controls.h"
#include "game.h"
#include "game/game.h"
#include "graphics/game.h"
#include "graphics/graphics.h"
#include "menu.h"
#include "utils/stringbuilder.h"

#define LOOP_CONTINUE 0x0
#define LOOP_STOP_WIN 0x1
#define LOOP_STOP_QUIT 0x2

u32 update_player(u32 player_id, u32 solution)
{
    NUContData *controller = ai_is_enabled(player_id)
                                 ? ai_controls_get(player_id)
                                 : controls_get(player_id);

    if (controller->trigger & A_BUTTON)
    {
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
    u32 virtual_card_count = get_virtual_card_count();
    s32 index = controls_get_index(player_id, card_count, virtual_card_count);
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
u32 game_solution;

void game_loop_init(u32 round_count, NUGfxFunc next_loop)
{
    game_round_count = round_count;
    game_next_loop = next_loop;
    game_solution = get_solution();
}

void game_loop(int pendingGfx)
{
    controls_update();

    u32 status = 0;
    status |= update_player(0, game_solution);
    status |= update_player(1, game_solution);
    status |= update_player(2, game_solution);
    status |= update_player(3, game_solution);

    if (status & LOOP_STOP_WIN)
    {
        game_round_count--;
        if (game_round_count > 0)
        {
            reset_cursors();
            shuffle_game();
            ai_init(get_settings(), get_cards(), get_dice(), get_cursors());
            game_solution = get_solution();
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
        cards_to_gfx(&graphics.card_count, &graphics.virtual_card_count, graphics.card_gfx_ids);
        graphics.dice_count = dice_to_gfx(graphics.dice_gfx_ids);
        graphics.cursor_count = cursors_to_gfx(graphics.cursors);

        char score[8];

        score_to_string(0, score);
        sb_init(&graphics.strings[0]);
        sb_color(&graphics.strings[0], SB_COLOR_WHITE);
        sb_append(&graphics.strings[0], score);
        sb_halign(&graphics.strings[0], -1, 20);
        sb_valign(&graphics.strings[0], 1, 20);

        score_to_string(1, score);
        sb_init(&graphics.strings[1]);
        sb_color(&graphics.strings[1], SB_COLOR_WHITE);
        sb_append(&graphics.strings[1], score);
        sb_halign(&graphics.strings[1], 1, 20);
        sb_valign(&graphics.strings[1], 1, 20);

        score_to_string(2, score);
        sb_init(&graphics.strings[2]);
        sb_color(&graphics.strings[2], SB_COLOR_WHITE);
        sb_append(&graphics.strings[2], score);
        sb_halign(&graphics.strings[2], -1, 20);
        sb_valign(&graphics.strings[2], -1, 20);

        score_to_string(3, score);
        sb_init(&graphics.strings[3]);
        sb_color(&graphics.strings[3], SB_COLOR_WHITE);
        sb_append(&graphics.strings[3], score);
        sb_halign(&graphics.strings[3], 1, 20);
        sb_valign(&graphics.strings[3], -1, 20);

        if (pendingGfx < 1)
        {
            render_game();
        }
    }
}
