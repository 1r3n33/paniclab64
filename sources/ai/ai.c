#include "ai.h"

NUContData controllers[NU_CONT_MAXCONTROLLERS] = {0};

s32 ai_players[NU_CONT_MAXCONTROLLERS] = {0};
s32 ai_states[NU_CONT_MAXCONTROLLERS] = {0};
s32 ai_targets[NU_CONT_MAXCONTROLLERS] = {0};
s32 ai_dirs[NU_CONT_MAXCONTROLLERS] = {0};

Settings *ai_settings;
Cards *ai_cards;
Dice *ai_dice;
Cursors *ai_cursors;

int ai_tick(u32 player_id);

void ai_init(Settings *settings, Cards *cards, Dice *dice, Cursors *cursors)
{
    ai_players[0] = (settings->players[0] == 2) ? 1 : 0;
    ai_players[1] = (settings->players[1] == 2) ? 1 : 0;
    ai_players[2] = (settings->players[2] == 2) ? 1 : 0;
    ai_players[3] = (settings->players[3] == 2) ? 1 : 0;

    ai_states[0] = 0;
    ai_states[1] = 0;
    ai_states[2] = 0;
    ai_states[3] = 0;

    ai_targets[0] = 0;
    ai_targets[1] = 0;
    ai_targets[2] = 0;
    ai_targets[3] = 0;

    ai_dirs[0] = 0;
    ai_dirs[1] = 0;
    ai_dirs[2] = 0;
    ai_dirs[3] = 0;

    ai_settings = settings;
    ai_cards = cards;
    ai_dice = dice;
    ai_cursors = cursors;
}

u32 ai_is_enabled(u32 player_id)
{
    return ai_players[player_id];
}

NUContData *ai_controls_get(u32 player_id)
{
    ai_states[player_id] = ai_tick(player_id);

    s32 dir = ai_dirs[player_id];
    if (dir != 0)
    {
        controllers[player_id].trigger = dir > 0 ? L_JPAD : R_JPAD;
    }
    else
    {
        controllers[player_id].trigger = 0;
    }

    return &controllers[player_id];
}

int ai_compute_initial_target(u32 player_id)
{
    if (ai_settings->flags == 0)
    {
        ai_targets[player_id] = ai_cursors->pos[player_id];
        return 1;
    }

    // get dice value
    u32 dir = ai_dice->dir;

    s32 target = -1;
    switch (dir)
    {
    case 0: // blue-black clockwise
    case 1: // blue-white anti-clockwise
        target = ai_cards->blue_dir;
        break;

    case 2: // yellow-black clockwise
    case 3: // yellow-white anti-clockwise
        target = ai_cards->yellow_dir;
        break;

    case 4: // red-black clockwise
    case 5: // red-white anti-clockwise
        target = ai_cards->red_dir;
        break;
    }

    ai_targets[player_id] = target;

    return 1;
}

int ai_advance_to_target(u32 player_id)
{
    s32 cur = ai_cursors->pos[player_id];
    s32 target = ai_targets[player_id];

    s32 diff = target - cur;
    if (diff == 0)
    {
        ai_dirs[player_id] = 0;
        return 2;
    }

    s32 dir = diff > 0 ? +1 : -1;

    s32 abs_diff = diff < 0 ? -diff : diff;
    if (abs_diff > ai_cards->count / 2)
    {
        dir = -dir;
    }

    ai_dirs[player_id] = dir;

    return 1;
}

int ai_tick(u32 player_id)
{
    s32 state = ai_states[player_id];
    switch (state)
    {
    case 0:
        state = ai_compute_initial_target(player_id);
        break;

    case 1:
        state = ai_advance_to_target(player_id);
        break;
    }

    return state;
}
