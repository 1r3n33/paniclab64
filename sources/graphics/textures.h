#ifndef TEXTURES_H
#define TEXTURES_H

#include <nusys.h>

#define TEXID_CARD_SQUID_STRIPES_BLUE 0
#define TEXID_CARD_SLUG_STRIPES_BLUE 1
#define TEXID_CARD_SQUID_DOTS_BLUE 2
#define TEXID_CARD_SLUG_DOTS_BLUE 3
#define TEXID_CARD_SQUID_STRIPES_ORANGE 4
#define TEXID_CARD_SLUG_STRIPES_ORANGE 5
#define TEXID_CARD_SQUID_DOTS_ORANGE 6
#define TEXID_CARD_SLUG_DOTS_ORANGE 7
#define TEXID_CARD_DIR_BLUE 8
#define TEXID_CARD_DIR_YELLOW 9
#define TEXID_CARD_DIR_RED 10
#define TEXID_CARD_SWAP_SHAPE 11
#define TEXID_CARD_SWAP_PATTERN 12
#define TEXID_CARD_SWAP_COLOR 13
#define TEXID_CARD_VENT 14
#define TEXID_DICE_SQUID 15
#define TEXID_DICE_SLUG 16
#define TEXID_DICE_STRIPES 17
#define TEXID_DICE_DOTS 18
#define TEXID_DICE_BLUE 19
#define TEXID_DICE_ORANGE 20
#define TEXID_DICE_DIR_BLUE_BLACK 21
#define TEXID_DICE_DIR_BLUE_WHITE 22
#define TEXID_DICE_DIR_YELLOW_BLACK 23
#define TEXID_DICE_DIR_YELLOW_WHITE 24
#define TEXID_DICE_DIR_RED_BLACK 25
#define TEXID_DICE_DIR_RED_WHITE 26

Gfx *apply_texture(Gfx *gfx, u32 tex_id);

#endif // TEXTURES_H
