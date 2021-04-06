#include <nusys.h>
#include "controls/controls.h"
#include "game.h"
#include "game/game.h"
#include "graphics/story.h"
#include "story.h"

void story_loop(int pending_gfx)
{
    controls_update();
    NUContData *controller = controls_get(0);

    if (controller->trigger)
    {
        init_game(1, SETTINGS_FLAG_SHAPE_0);
        shuffle_game();
        game_loop_init(1, (NUGfxFunc)story_loop);
        nuGfxFuncSet((NUGfxFunc)game_loop);
    }

    if (pending_gfx < 1)
    {
        render_story();
    }
}
