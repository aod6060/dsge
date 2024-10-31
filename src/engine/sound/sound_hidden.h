#ifndef SOUND_HIDDEN_H
#define SOUND_HIDDEN_H


#include "../sys.h"
#include "SDL_mixer.h"



namespace sound {

    // I'm not feelling this...
    /*
    struct Music {
        Mix_Music* music;
        bool isLooping = true;
    };

    struct SoundFX {

    }

    struct SoundFXPositional {
        
    }
    */

    Mix_Music* getMusicStream(std::string name);

    Mix_Chunk* getSoundFXStream(std::string name);

    glm::vec2 getListenerPosition();
}

#endif