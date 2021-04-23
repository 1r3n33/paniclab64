#include "stringbuilder.h"
#include "../graphics/fonts.h"
#include "../graphics/init.h"

void sb_init(String *s)
{
    s->b[0] = 0;
    s->p = s->b;
    s->w = 0;
    s->x = 0;
    s->y = 0;
}

void sb_append(String *s, char *in)
{
    while (*in)
    {
        *(s->p) = *in;
        s->w += fonts_get_width(*in);

        s->p++;
        in++;
    }
    *(s->p) = 0;
}

void sb_color(String *s, char color_id)
{
    *(s->p) = color_id;
    s->p++;
    *(s->p) = 0;
}

void sb_halign(String *s, u32 h, s32 border)
{
    switch (h)
    {
    case -1:
        s->x = (-SCREEN_WD / 2) + border;
        break;

    case 0:
        s->x = -s->w / 2;
        break;

    case 1:
        s->x = ((SCREEN_WD / 2) - s->w) - border;
        break;
    }
}

void sb_valign(String *s, u32 v, s32 border)
{
    switch (v)
    {
    case -1:
        s->y = (-SCREEN_HT / 2) + border;
        break;

    case 0:
        s->y = -10 / 2;
        break;

    case 1:
        s->y = ((SCREEN_HT / 2) - 10) - border;
        break;
    }
}
