#include "ai.h"

NUContData zero = {0};

u32 ai_players[NU_CONT_MAXCONTROLLERS] = {0};
u32 ai_states[NU_CONT_MAXCONTROLLERS] = {0};

void ai_init(u32 settings_players[4])
{
    ai_players[0] = (settings_players[0] == 2) ? 1 : 0;
    ai_players[1] = (settings_players[1] == 2) ? 1 : 0;
    ai_players[2] = (settings_players[2] == 2) ? 1 : 0;
    ai_players[3] = (settings_players[3] == 2) ? 1 : 0;
}

u32 ai_is_enabled(u32 player_id)
{
    return ai_players[player_id];
}

NUContData *ai_controls_get(u32 player_id)
{
    zero.trigger = L_JPAD;
    return &zero;
}
