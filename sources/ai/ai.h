#ifndef AI_H
#define AI_H

#include <nusys.h>
#include "../game/cards.h"
#include "../game/cursors.h"
#include "../game/dice.h"
#include "../game/settings.h"

void ai_init(Settings *settings, Cards *cards, Dice *dice, Cursors *cursors);

u32 ai_is_enabled(u32 player_id);

NUContData *ai_controls_get(u32 player_id);

#endif // AI_H
