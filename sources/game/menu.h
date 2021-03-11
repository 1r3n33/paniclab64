#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <nusys.h>

void init_menu();

void menu_up();
void menu_down();
void menu_left();
void menu_right();

// Return -1 if selection is BACK
// Return +1 if selection is START/RESUME
// else return 0
s32 menu_action();

// Map to graphics data
u32 menu_to_gfx(char text[32][32]);

#endif // GAME_MENU_H
