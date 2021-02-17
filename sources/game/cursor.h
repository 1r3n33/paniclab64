#ifndef CURSOR_H
#define CURSOR_H

#include <nusys.h>

typedef struct
{
    u32 card_count;
    s32 cur_pos;
} Cursor;

// Init cursor
void init_cursor(Cursor *cursor);

// Move cursor
void move_cursor(Cursor *cursor, s32 dir);

#endif // CURSOR_H
