#include "settings.h"

Settings settings;

Settings *get_settings()
{
    return &settings;
}

void init_settings()
{
    settings.players[0] = SETTINGS_PLAYER_ON;
    settings.players[1] = SETTINGS_PLAYER_OFF;
    settings.players[2] = SETTINGS_PLAYER_OFF;
    settings.players[3] = SETTINGS_PLAYER_OFF;
    settings.flags = SETTINGS_FLAG_MUTATIONS | SETTINGS_FLAG_AIRVENTS | SETTINGS_FLAG_SHAPE_0 | SETTINGS_FLAG_SHAPE_1;
}

void change_settings_player(s32 player_id, s32 d)
{
    s32 value = (s32)settings.players[player_id] + d;
    if (value > SETTINGS_PLAYER_AI)
    {
        value = SETTINGS_PLAYER_OFF;
    }
    else if (value < 0)
    {
        value = SETTINGS_PLAYER_AI;
    }
    settings.players[player_id] = value;
}

void change_settings_flags(u32 settings_flags)
{
    settings.flags ^= settings_flags;
}

u32 get_settings_player_count()
{
    u32 p1 = settings.players[0] != SETTINGS_PLAYER_OFF ? 1 : 0;
    u32 p2 = settings.players[1] != SETTINGS_PLAYER_OFF ? 1 : 0;
    u32 p3 = settings.players[2] != SETTINGS_PLAYER_OFF ? 1 : 0;
    u32 p4 = settings.players[3] != SETTINGS_PLAYER_OFF ? 1 : 0;
    return p1 + p2 + p3 + p4;
}

u32 get_settings_flags()
{
    return settings.flags;
}

char *get_settings_player_string(u32 player_id)
{
    switch (settings.players[player_id])
    {
    case SETTINGS_PLAYER_OFF:
        return "Off";

    case SETTINGS_PLAYER_ON:
        return "On";

    case SETTINGS_PLAYER_AI:
        return "AI";
    }
}

char *get_settings_flags_string(u32 flag)
{
    if (settings.flags & flag)
    {
        return "On";
    }
    else
    {
        return "Off";
    }
}
