#ifndef GAME_H
#define GAME_H

void game_loop_init(u32 round_count, NUGfxFunc next_loop);

void game_loop(int pendingGfx);

#endif // GAME_H
