#include <nusys.h>
#include "game/game.h"
#include "game/menu.h"
#include "graphics/graphics.h"
#include "graphics/game.h"
#include "graphics/menu.h"
#include "graphics/titlescreen.h"

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
  graphics.card_count = cards_to_gfx(graphics.card_gfx_ids);
  cursors_to_gfx(graphics.cursors);
  score_to_string(0, graphics.text[0]);
  score_to_string(1, graphics.text[1]);

  if (pendingGfx < 1)
  {
    render_game(&game);
  }
}

void titlescreen_loop(int pendingGfx);

void menu_loop(int pendingGfx)
{
  nuContDataGetExAll(contdata);
  if (contdata[0].trigger & START_BUTTON)
  {
    nuGfxFuncSet((NUGfxFunc)game_loop);
  }

  if (contdata[0].trigger & A_BUTTON)
  {
    s32 next = menu_action();
    if (next < 0)
    {
      nuGfxFuncSet((NUGfxFunc)titlescreen_loop);
    }
    else if (next > 0)
    {
      nuGfxFuncSet((NUGfxFunc)game_loop);
    }
  }

  if (contdata[0].trigger & U_JPAD)
  {
    menu_up();
  }

  if (contdata[0].trigger & D_JPAD)
  {
    menu_down();
  }

  if (contdata[0].trigger & L_JPAD)
  {
    menu_left();
  }

  if (contdata[0].trigger & R_JPAD)
  {
    menu_right();
  }

  menu_to_gfx(graphics.text);

  if (pendingGfx < 1)
  {
    render_menu();
  }
}

void titlescreen_loop(int pendingGfx)
{
  nuContDataGetExAll(contdata);
  if (contdata[0].trigger & START_BUTTON)
  {
    nuGfxFuncSet((NUGfxFunc)menu_loop);
  }

  if (pendingGfx < 1)
  {
    render_titlescreen();
  }
}

void mainproc(void)
{
  init_menu();
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
