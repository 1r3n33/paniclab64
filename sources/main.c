#include <nusys.h>
#include "game/game.h"

/* Declaration of the prototype */
void stage00(int);
void makeDL00(Game* game);

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

  while(1)
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

  if (contdata[0].trigger & L_JPAD)
  {
    game.cursor.cur_pos++;
    if (game.cursor.cur_pos >= game.cursor.card_count)
    {
      game.cursor.cur_pos = 0;
    }
  }

  if (contdata[0].trigger & R_JPAD)
  {
    if (game.cursor.cur_pos == 0)
    {
      game.cursor.cur_pos = game.cursor.card_count-1;
    }
    else
    {
      game.cursor.cur_pos--;
    }
  }

  // Shuffle cards
  if(contdata[0].trigger & START_BUTTON)
  {
    shuffle_game(&game);
  }

  // It provides the display process if there is no RCP task that is processing.
  if(pendingGfx < 1)
  {
    makeDL00(&game);
  }
}
