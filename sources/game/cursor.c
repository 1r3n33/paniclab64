#include "cursor.h"

void init_cursor(Cursor *cursor)
{
    cursor->card_count = 16; // Number of cards
    cursor->cur_pos = 0;
}

void move_cursor(Cursor *cursor, s32 dir)
{
    cursor->cur_pos += dir;
    while (cursor->cur_pos < 0)
    {
        cursor->cur_pos += cursor->card_count;
    }
    while (cursor->cur_pos >= cursor->card_count)
    {
        cursor->cur_pos -= cursor->card_count;
    }
}
