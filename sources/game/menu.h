#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <nusys.h>
#include "../utils/string.h"

void init_menu();

u32 menu_up();
u32 menu_down();
u32 menu_left();
u32 menu_right();

// Return -1 if selection is BACK
// Return +1 if selection is START/RESUME
// else return 0
s32 menu_action();

// Map to graphics data
u32 menu_to_gfx(String strings[32]);

#endif // GAME_MENU_H
