#ifndef SOUND_HIDDEN_H
#define SOUND_HIDDEN_H


#include "../sys.h"
#include "SDL_mixer.h"



namespace sound {
    
    Mix_Music* getMusicStream(std::string name);

    Mix_Chunk* getSoundFXStream(std::string name);

    glm::vec2 getListenerPosition();
}

#endif