#include "cursors.h"

Cursors cursors;

Cursors *get_cursors()
{
    return &cursors;
}

void init_cursors(u32 player_count, u32 card_count)
{
    cursors.player_count = player_count;
    cursors.card_count = card_count;
    reset_cursors();
}

void reset_cursors()
{
    switch (cursors.player_count)
    {
    case 1:
        cursors.pos[0] = 0;
        break;

    case 2:
        cursors.pos[0] = cursors.card_count / 4;
        cursors.pos[1] = cursors.card_count - cursors.pos[0];
        break;

    case 3:
        cursors.pos[0] = 0;
        cursors.pos[1] = cursors.card_count / 3;
        cursors.pos[2] = cursors.card_count - cursors.pos[1];
        break;

    case 4:
        cursors.pos[0] = cursors.card_count / 8;
        cursors.pos[1] = cursors.pos[0] * 3;
        cursors.pos[2] = cursors.card_count - cursors.pos[1];
        cursors.pos[3] = cursors.card_count - cursors.pos[0];
        break;
    }
}

// Set cursor
void set_cursor(u32 player_id, u32 value)
{
    cursors.pos[player_id] = value;
}

void move_cursor(u32 player_id, s32 dir)
{
    cursors.pos[player_id] += dir;
    while (cursors.pos[player_id] < 0)
    {
        cursors.pos[player_id] += cursors.card_count;
    }
    while (cursors.pos[player_id] >= cursors.card_count)
    {
        cursors.pos[player_id] -= cursors.card_count;
    }
}

int cursor_equals(u32 player_id, u32 value)
{
    return cursors.pos[player_id] == value;
}

// Map to graphics data
u32 cursors_to_gfx(u32 *gfx_cursors)
{
    gfx_cursors[0] = cursors.pos[0];
    gfx_cursors[1] = cursors.pos[1];
    gfx_cursors[2] = cursors.pos[2];
    gfx_cursors[3] = cursors.pos[3];

    return cursors.player_count;
}
