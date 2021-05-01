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

s32 controls_get_index(u32 player_id, u32 card_count, u32 virtual_card_count)
{
    if (controls.data[player_id].stick_x < -30 ||
        controls.data[player_id].stick_x > +30 ||
        controls.data[player_id].stick_y < -30 ||
        controls.data[player_id].stick_y > +30)
    {

        f32 x = ((f32)controls.data[player_id].stick_x) / 128.0f;
        f32 y = ((f32)controls.data[player_id].stick_y) / 128.0f;

        // Get coordinates in the -pi..+pi range (-pi is left)
        f32 a = atan2f(y, x);

        // Shift -pi to north (north is usualy the first card index)
        f32 sa = a + (0.5f * (f32)M_PI);

        // If virtual circle is active, shift -pi to first card index
        u32 diff = (virtual_card_count - card_count);
        if (diff)
        {
            u32 count = (diff & 1) ? card_count : card_count - 1;
            sa = sa + ((((f32)count / 2.0f) * (1.0f / (f32)virtual_card_count) * ((f32)M_PI * 2.0f)));
        }

        // Center to -pi..pi
        while (sa < -(f32)M_PI)
            sa += 2.0f * (f32)M_PI;
        while (sa > (f32)M_PI)
            sa -= 2.0f * (f32)M_PI;

        // Scale to 0..1
        f32 b = (sa + (f32)M_PI) / (2.0f * (f32)M_PI);

        // Scale to 0..n (0 matches first card index)
        f32 c = b * (f32)virtual_card_count;

        // To index on the virtual circle (0..n-1)
        s32 r = ((u32)c) % virtual_card_count;

        // If virtual circle is active, check if out of range
        if (diff > 0 && r >= card_count)
        {
            return -1;
        }
        else
        {
            return r;
        }
    }
    else
    {
        return -1;
    }
}
