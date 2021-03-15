#include <math.h>
#include "controls.h"

Controls controls;

void controls_init()
{
    nuContInit();
    controls.stick_throttling[0] = 0;
    controls.stick_throttling[1] = 0;
    controls.stick_throttling[2] = 0;
    controls.stick_throttling[3] = 0;
}

void controls_update()
{
    nuContDataGetExAll(controls.data);
    for (u32 i = 0; i < NU_CONT_MAXCONTROLLERS; i++)
    {
        if (controls.stick_throttling[i] > 0)
        {
            if (controls.data[i].stick_x > -50 &&
                controls.data[i].stick_x < +50 &&
                controls.data[i].stick_y > -50 &&
                controls.data[i].stick_y < +50)
            {
                controls.stick_throttling[i] = 0;
            }
            else
            {
                controls.stick_throttling[i]--;
                controls.data[i].stick_x = 0;
                controls.data[i].stick_y = 0;
            }
        }
        else
        {
            if (controls.data[i].stick_x < -50 ||
                controls.data[i].stick_x > +50 ||
                controls.data[i].stick_y < -50 ||
                controls.data[i].stick_y > +50)
            {
                controls.stick_throttling[i] = 8;
            }
        }
    }
}

NUContData *controls_get(u32 player_id)
{
    return controls.data + player_id;
}

s32 controls_get_index(u32 player_id, u32 count)
{
    if (controls.data[player_id].stick_x < -30 ||
        controls.data[player_id].stick_x > +30 ||
        controls.data[player_id].stick_y < -30 ||
        controls.data[player_id].stick_y > +30)
    {
        f32 x = ((f32)controls.data[player_id].stick_x) / 128.0f;
        f32 y = ((f32)controls.data[player_id].stick_y) / 128.0f;
        f32 a = atan2f(y, x);            // -pi..pi (-pi is left)
        f32 sa = a + (0.5f * (f32)M_PI); // shifted so -pi is north
        while (sa > (f32)M_PI)
            sa -= 2.0f * (f32)M_PI;                    // recentered to -pi..pi
        f32 b = (sa + (f32)M_PI) / (2.0f * (f32)M_PI); // 0..1
        f32 c = b * (f32)count;                        // 0..n (0 is north and it matches first card index)
        return ((u32)c) % count;                       // 0..n-1
    }
    else
    {
        return -1;
    }
}
