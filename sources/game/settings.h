#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <nusys.h>

#define SETTINGS_PLAYER_OFF 0
#define SETTINGS_PLAYER_ON 1
#define SETTINGS_PLAYER_AI 2

#define SETTINGS_FLAG_AIRVENTS 0x02

#define SETTINGS_FLAG_SHAPE_0 0x04
#define SETTINGS_FLAG_SHAPE_1 0x08
#define SETTINGS_FLAG_SHAPE_ALL (SETTINGS_FLAG_SHAPE_0 | SETTINGS_FLAG_SHAPE_1)

#define SETTINGS_FLAG_MUTATION_0 0x10
#define SETTINGS_FLAG_MUTATION_1 0x20
#define SETTINGS_FLAG_MUTATION_2 0x40
#define SETTINGS_FLAG_MUTATION_ALL (SETTINGS_FLAG_MUTATION_0 | SETTINGS_FLAG_MUTATION_1 | SETTINGS_FLAG_MUTATION_2)

typedef struct
{
    u32 players[NU_CONT_MAXCONTROLLERS];
    u32 flags;
} Settings;

Settings *get_settings();

void init_settings();

void settings_set_player(u32 player_id, u32 value);

void change_settings_player(s32 player_id, s32 d);

void change_settings_flags(u32 settings_flags);

u32 get_settings_player_count();

u32 get_settings_flags();

char *get_settings_player_string(u32 player_id);

char *get_settings_flags_string(u32 flag);

#endif // GAME_SETTINGS_H
