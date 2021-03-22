#ifndef CURSOR_H
#define CURSOR_H

#include <nusys.h>

typedef struct
{
    u32 player_count;
    u32 card_count;
    s32 pos[4];
} Cursors;

Cursors *get_cursors();

// Init all cursors
void init_cursors(u32 player_count, u32 card_count);

// Reset all cursors
void reset_cursors();

// Set cursor
void set_cursor(u32 player_id, u32 value);

// Move cursor
void move_cursor(u32 player_id, s32 dir);

// Check cursor
int cursor_equals(u32 player_id, u32 value);

// Map to graphics data
u32 cursors_to_gfx(u32 *gfx_cursors);

#endif // CURSOR_H
