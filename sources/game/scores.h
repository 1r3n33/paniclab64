#ifndef SCORE_H
#define SCORE_H

#include <nusys.h>

// Reset 4 players scores to zero
void init_scores();

void add_to_score(u32 player_id, s32 points);

// str must be large enough to hold 7 chars + 0
void score_to_string(u32 player_id, char *str);

#endif // SCORE_H
