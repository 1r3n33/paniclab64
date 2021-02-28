#include "scores.h"

s32 scores[4];

void init_scores()
{
    scores[0] = 0;
    scores[1] = 0;
    scores[2] = 0;
    scores[3] = 0;
}

void add_to_score(u32 player_id, s32 points)
{
    scores[player_id] += points;
    if (scores[player_id] < 0)
    {
        scores[player_id] = 0;
    }
}

void score_to_string(u32 player_id, char *str)
{
    u32 i;
    for (i = 0; i < 7; i++)
    {
        str[i] = '0';
    }
    str[i] = 0;
    i--;

    u32 sc = scores[player_id];
    while (sc && i)
    {
        u32 q = sc / 10;
        u32 r = sc % 10;
        str[i--] = '0' + r;
        sc = q;
    }
}
