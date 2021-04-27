#ifndef GAME_STORY_H
#define GAME_STORY_H

#include <nusys.h>
#include "../utils/string.h"

void story_init();

u32 story_up();
u32 story_down();
u32 story_left();
u32 story_right();

// Return -1 if selection is BACK
// Return +1 if selection is START/RESUME
// else return 0
s32 story_action();

// Map to graphics data
u32 story_to_gfx(String strings[32]);

u32 story_get_current_level();

#endif // GAME_STORY_H
