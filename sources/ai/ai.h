#ifndef AI_H
#define AI_H

#include <nusys.h>

void ai_init(u32 settings_players[4]);

u32 ai_is_enabled(u32 player_id);

NUContData *ai_controls_get(u32 player_id);

#endif // AI_H