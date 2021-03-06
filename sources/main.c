#include <nusys.h>
#include "audio/audio.h"
#include "controls/controls.h"
#include "titlescreen.h"

void mainproc(void)
{
    // Initialization of graphics
    nuGfxInit();

    // Initialization of controllers
    controls_init();

    audio_init();

    // Register call-back
    nuGfxFuncSet((NUGfxFunc)titlescreen_loop);

    // The screen display ON
    nuGfxDisplayOn();

    while (1)
    {
    }
}
