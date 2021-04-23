#ifndef UTILS_STRINGBUILDER_H
#define UTILS_STRINGBUILDER_H

#include <nusys.h>

#define SB_COLOR_BLACK 1
#define SB_COLOR_BLUE 2
#define SB_COLOR_PURPLE 3
#define SB_COLOR_ORANGE 4
#define SB_COLOR_RED 5
#define SB_COLOR_YELLOW 6
#define SB_COLOR_GREEN 7
#define SB_COLOR_WHITE 8

typedef struct
{
    char b[32];
    char *p;
    s32 w;
    s32 x;
    s32 y;
} String;

void sb_init(String *s);
void sb_append(String *s, char *in);
void sb_color(String *s, char color_id);
void sb_halign(String *s, u32 h, s32 border);
void sb_valign(String *s, u32 v, s32 border);

#endif // UTILS_STRINGBUILDER_H
