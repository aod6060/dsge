#ifndef SOUND_HIDDEN_H
#define SOUND_HIDDEN_H


#include "../sys.h"
#include "SDL_mixer.h"



namespace sound {

    struct Music {
        Mix_Music* music;
        bool isLooping = true;
    };

    struct SoundFX {

    }

    struct SoundFXPositional {
        
    }
}

#endif