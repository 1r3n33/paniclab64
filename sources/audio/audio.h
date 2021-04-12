#ifndef AUDIO_AUDIO_H
#define AUDIO_AUDIO_H

#include <nusys.h>
#include "../../assets/sounds/sfx.h"

void audio_init();

void audio_play_sfx(u32 id);

#endif // AUDIO_AUDIO_H
