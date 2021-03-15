#include <nusys.h>
#include "controls/controls.h"
#include "game/game.h"
#include "game/menu.h"
#include "graphics/graphics.h"
#include "graphics/game.h"
#include "graphics/menu.h"
#include "graphics/titlescreen.h"

void menu_loop(int pendingGfx);
void titlescreen_loop(int pendingGfx);

void update_player(u32 player_id)
{
  NUContData *controller = controls_get(player_id);

  if (controller->trigger & A_BUTTON)
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

  if (controller->trigger & L_JPAD)
  {
    move_cursor(player_id, 1);
  }

  if (controller->trigger & R_JPAD)
  {
    move_cursor(player_id, -1);
  }

  s32 index = controls_get_index(player_id, game.card_count);
  if (index >= 0)
  {
    set_cursor(player_id, index);
  }

  // Shuffle cards
  if (controller->trigger & START_BUTTON)
  {
    nuGfxFuncSet((NUGfxFunc)menu_loop);
  }
}

void game_loop(int pendingGfx)
{
  controls_update();

  update_player(0);
  update_player(1);
  update_player(2);
  update_player(3);

  // Map game data to graphics data
  graphics.card_count = cards_to_gfx(graphics.card_gfx_ids);
  graphics.dice_count = dice_to_gfx(&game.dice, graphics.dice_gfx_ids);
  graphics.cursor_count = cursors_to_gfx(graphics.cursors);
  score_to_string(0, graphics.text[0]);
  score_to_string(1, graphics.text[1]);
  score_to_string(2, graphics.text[2]);
  score_to_string(3, graphics.text[3]);

  if (pendingGfx < 1)
  {
    render_game(&game);
  }
}

void menu_loop(int pendingGfx)
{
  controls_update();
  NUContData *controller = controls_get(0);

  if (controller->trigger & START_BUTTON)
  {
    u32 player_count = get_settings_player_count();
    u32 settings_flags = get_settings_flags();
    init_game(&game, player_count, settings_flags);
    shuffle_game(&game);
    nuGfxFuncSet((NUGfxFunc)game_loop);
  }

  if (controller->trigger & A_BUTTON)
  {
    s32 next = menu_action();
    if (next < 0)
    {
      nuGfxFuncSet((NUGfxFunc)titlescreen_loop);
    }
    else if (next > 0)
    {
      u32 player_count = get_settings_player_count();
      u32 settings_flags = get_settings_flags();
      init_game(&game, player_count, settings_flags);
      shuffle_game(&game);
      nuGfxFuncSet((NUGfxFunc)game_loop);
    }
  }

  if (controller->trigger & U_JPAD || controller->stick_y > 50)
  {
    menu_up();
  }

  if (controller->trigger & D_JPAD || controller->stick_y < -50)
  {
    menu_down();
  }

  if (controller->trigger & L_JPAD || controller->stick_x < -50)
  {
    menu_left();
  }

  if (controller->trigger & R_JPAD || controller->stick_x > 50)
  {
    menu_right();
  }

  graphics.selection = menu_to_gfx(graphics.text);

  if (pendingGfx < 1)
  {
    render_menu();
  }
}

void titlescreen_loop(int pendingGfx)
{
  controls_update();
  NUContData *controller = controls_get(0);

  if (controller->trigger & START_BUTTON)
  {
    init_menu();
    nuGfxFuncSet((NUGfxFunc)menu_loop);
  }

  if (pendingGfx < 1)
  {
    render_titlescreen();
  }
}

void mainproc(void)
{
  // Initialization of graphics
  nuGfxInit();

  // Initialization of controllers
  controls_init();

  // Register call-back
  nuGfxFuncSet((NUGfxFunc)titlescreen_loop);

  // The screen display ON
  nuGfxDisplayOn();

  while (1)
  {
  }
}
