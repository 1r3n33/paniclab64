#include <nusys.h>
#include "game/game.h"
#include "graphics/graphics.h"

/* Declaration of the prototype */
void update(int);
void makeDL00(Game *game);

NUContData contdata[MAXCONTROLLERS];

/*------------------------
  Main
--------------------------*/
void mainproc(void)
{
  init_game(&game);
  shuffle_game(&game);

  // Initialization of graphics
  nuGfxInit();

  // Initialization of controllers
  nuContInit();

  // Register call-back
  nuGfxFuncSet((NUGfxFunc)update);

  // The screen display ON
  nuGfxDisplayOn();

  while (1)
  {
  }
}

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

/*-----------------------------------------------------------------------------
  The call-back function

  pendingGfx which is passed from Nusystem as the argument of the call-back
  function is the total number of RCP tasks that are currently processing
  and waiting for the process.
-----------------------------------------------------------------------------*/
void update(int pendingGfx)
{
  nuContDataGetExAll(contdata);

  update_player(0);
  update_player(1);

  // Map game data to graphics data
  cursors_to_gfx(graphics.cursors);
  score_to_string(0, graphics.text[0]);
  score_to_string(1, graphics.text[1]);

  // It provides the display process if there is no RCP task that is processing.
  if (pendingGfx < 1)
  {
    makeDL00(&game);
  }
}
