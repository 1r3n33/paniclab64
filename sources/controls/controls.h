#ifndef CONTROLS_H
#define CONTROLS_H

#include <nusys.h>

typedef struct
{
    NUContData data[NU_CONT_MAXCONTROLLERS];
    u32 stick_throttling[NU_CONT_MAXCONTROLLERS];
} Controls;

void controls_init();

// call once at the beginning of the frame
void controls_update();

NUContData *controls_get(u32 player_id);

s32 controls_get_index(u32 player_id, u32 count);

#endif // CONTROLS_H
