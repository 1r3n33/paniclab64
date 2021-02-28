#include <nusys.h>
#include "game/game.h"
#include "graphics/graphics.h"

/* Declaration of the prototype */
void stage00(int);
void makeDL00(Game *game);

// Controller data
NUContData contdata[1];

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
  nuGfxFuncSet((NUGfxFunc)stage00);

  // The screen display ON
  nuGfxDisplayOn();

  while (1)
  {
  }
}

/*-----------------------------------------------------------------------------
  The call-back function

  pendingGfx which is passed from Nusystem as the argument of the call-back
  function is the total number of RCP tasks that are currently processing
  and waiting for the process.
-----------------------------------------------------------------------------*/
void stage00(int pendingGfx)
{
  // Read data of controller 1
  nuContDataGetEx(contdata, 0);

  if (contdata[0].trigger & A_BUTTON)
  {
    u32 res = check_selection(&game);
    if (res > 0)
    {
      add_to_score(0, 100);
      reset_cursor(&game.cursor);
      shuffle_game(&game);
    }
    else
    {
      add_to_score(0, -50);
    }
  }

  if (contdata[0].trigger & L_JPAD)
  {
    move_cursor(&game.cursor, 1);
  }

  if (contdata[0].trigger & R_JPAD)
  {
    move_cursor(&game.cursor, -1);
  }

  // Shuffle cards
  if (contdata[0].trigger & START_BUTTON)
  {
    shuffle_game(&game);
  }

  // Map game data to graphics data
  score_to_string(0, graphics.text[0]);
  score_to_string(1, graphics.text[1]);

  // It provides the display process if there is no RCP task that is processing.
  if (pendingGfx < 1)
  {
    makeDL00(&game);
  }
}
