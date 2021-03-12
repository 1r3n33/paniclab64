#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <nusys.h>

#define SETTINGS_PLAYER_OFF 0
#define SETTINGS_PLAYER_ON 1
#define SETTINGS_PLAYER_AI 2

#define SETTINGS_FLAG_MUTATIONS 0x01
#define SETTINGS_FLAG_AIRVENTS 0x02

typedef struct
{
    u32 players[NU_CONT_MAXCONTROLLERS];
    u32 flags;
} Settings;

void init_settings();

void change_settings_player(s32 player_id, s32 d);

void change_settings_flags(u32 settings_flags);

u32 get_settings_player_count();

u32 get_settings_flags();

char *get_settings_player_string(u32 player_id);

char *get_settings_flags_string(u32 flag);

#endif // GAME_SETTINGS_H
