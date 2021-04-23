#ifndef FONTS_H
#define FONTS_H

#include <nusys.h>

u32 fonts_get_width(char c);

Gfx *render_string(Gfx *gfx, char *str, u32 mtx_id, f32 x, f32 y);

#endif // FONTS_H
