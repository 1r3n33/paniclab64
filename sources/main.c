#include <nusys.h>
#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/render.h"

void makeDL00(Game *game);

NUContData contdata[MAXCONTROLLERS];

void update_player(u32 player_id)
{
  if (contdata[player_id].trigger & A_BUTTON)
  {
    u32 solution = get_solution(&game);
    if (cursor_equals(player_id, solution))
    {
      add_to_score(player_id, 100);
      reset_cursors();
      shuffle_game(&game);
    }
    else
    {
      add_to_score(player_id, -50);
    }
  }

  if (contdata[player_id].trigger & L_JPAD)
  {
    move_cursor(player_id, 1);
  }

  if (contdata[player_id].trigger & R_JPAD)
  {
    move_cursor(player_id, -1);
  }

  // Shuffle cards
  if (contdata[player_id].trigger & START_BUTTON)
  {
    shuffle_game(&game);
  }
}

void game_loop(int pendingGfx)
{
  nuContDataGetExAll(contdata);

  update_player(0);
  update_player(1);

  // Map game data to graphics data
  cursors_to_gfx(graphics.cursors);
  score_to_string(0, graphics.text[0]);
  score_to_string(1, graphics.text[1]);

  if (pendingGfx < 1)
  {
    makeDL00(&game);
  }
}

void titlescreen_loop(int pendingGfx)
{
  nuContDataGetExAll(contdata);
  if (contdata[0].trigger & START_BUTTON)
  {
    nuGfxFuncSet((NUGfxFunc)game_loop);
  }

  if (pendingGfx < 1)
  {
    render_titlescreen();
  }
}

void mainproc(void)
{
  init_game(&game);
  shuffle_game(&game);

  // Initialization of graphics
  nuGfxInit();

  // Initialization of controllers
  nuContInit();

  // Register call-back
  nuGfxFuncSet((NUGfxFunc)titlescreen_loop);

  // The screen display ON
  nuGfxDisplayOn();

  while (1)
  {
  }
}
