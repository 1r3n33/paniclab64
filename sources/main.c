#include <math.h>
#include <nusys.h>
#include <stdlib.h>
#include "game/game.h"
#include "game/menu.h"
#include "graphics/graphics.h"
#include "graphics/game.h"
#include "graphics/menu.h"
#include "graphics/titlescreen.h"

NUContData contdata[MAXCONTROLLERS];

void menu_loop(int pendingGfx);
void titlescreen_loop(int pendingGfx);

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

  if (abs(contdata[player_id].stick_x) > 30 || abs(contdata[player_id].stick_y) > 30)
  {
    f32 x = ((f32)contdata[player_id].stick_x) / 128.0f;
    f32 y = ((f32)contdata[player_id].stick_y) / 128.0f;
    f32 a = atan2f(y, x);            // -pi..pi (-pi is left)
    f32 sa = a + (0.5f * (f32)M_PI); // shifted so -pi is north
    while (sa > (f32)M_PI)
      sa -= 2.0f * (f32)M_PI;                      // recentered to -pi..pi
    f32 b = (sa + (f32)M_PI) / (2.0f * (f32)M_PI); // 0..1
    f32 c = b * (f32)game.card_count;              // 0..n (0 is north and it matches first card index)
    u32 d = ((u32)c) % game.card_count;            // 0..n-1
    set_cursor(player_id, d);
  }

  // Shuffle cards
  if (contdata[player_id].trigger & START_BUTTON)
  {
    nuGfxFuncSet((NUGfxFunc)menu_loop);
  }
}

void game_loop(int pendingGfx)
{
  nuContDataGetExAll(contdata);

  update_player(0);
  update_player(1);

  // Map game data to graphics data
  graphics.card_count = cards_to_gfx(graphics.card_gfx_ids);
  graphics.dice_count = dice_to_gfx(&game.dice, graphics.dice_gfx_ids);
  graphics.cursor_count = cursors_to_gfx(graphics.cursors);
  score_to_string(0, graphics.text[0]);
  score_to_string(1, graphics.text[1]);

  if (pendingGfx < 1)
  {
    render_game(&game);
  }
}

u32 stick_throttling = 0;

void menu_loop(int pendingGfx)
{
  nuContDataGetExAll(contdata);
  if (stick_throttling > 0)
  {
    contdata[0].stick_x = 0;
    contdata[0].stick_y = 0;
    stick_throttling--;
  }

  if (contdata[0].trigger & START_BUTTON)
  {
    u32 player_count = get_settings_player_count();
    u32 settings_flags = get_settings_flags();
    init_game(&game, player_count, settings_flags);
    shuffle_game(&game);
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
      u32 player_count = get_settings_player_count();
      u32 settings_flags = get_settings_flags();
      init_game(&game, player_count, settings_flags);
      shuffle_game(&game);
      nuGfxFuncSet((NUGfxFunc)game_loop);
    }
  }

  if (contdata[0].trigger & U_JPAD || contdata[0].stick_y > 50)
  {
    menu_up();
    stick_throttling = 8;
  }

  if (contdata[0].trigger & D_JPAD || contdata[0].stick_y < -50)
  {
    menu_down();
    stick_throttling = 8;
  }

  if (contdata[0].trigger & L_JPAD || contdata[0].stick_x < -50)
  {
    menu_left();
    stick_throttling = 8;
  }

  if (contdata[0].trigger & R_JPAD || contdata[0].stick_x > 50)
  {
    menu_right();
    stick_throttling = 8;
  }

  graphics.selection = menu_to_gfx(graphics.text);

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
  nuContInit();

  // Register call-back
  nuGfxFuncSet((NUGfxFunc)titlescreen_loop);

  // The screen display ON
  nuGfxDisplayOn();

  while (1)
  {
  }
}
